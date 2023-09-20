#include <cstdint>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <fstream>

#include "../src/blackjack.cpp"

#define RLC_GET_FUNCTION_DECLS
#define RLC_GET_TYPE_DECLS

extern "C" {
    #include "include/rlc_names.h"
}

#ifndef FUZZING
#define out std::cout
#else
#define out std::ostream(nullptr)
#endif

/*
    Blackjack has 4 actions:
        - shuffle_deck()
        - deal()
        - take_card(int player)
        - pass(int player)
    
    We use the first byte to pick the number of players.
    We interpret the rest of fuzz input as a sequence of actions taken. 
    We use a byte to pick an action (because I don't want to deal with bits).
    If that action has an int parameter, we use the next sizeof(int) to pick the input.
*/
extern "C" int LLVMFuzzerTestOneInput(const char *Data, size_t Size) {
    blackjackEntity blackjack;
    int64_t two = 2;
    blackjackblackjackEntity_int64_t_(&blackjack, &two);

    int offset = 0;
    try {
        while(offset + 1 + sizeof(int64_t) < Size) // we consume at most 1 + sizeof (int) bytes per iteration.
        {
            switch (abs(*(Data + offset) % 2))
            {
                case 0:
                    out << "DRAW " << *(int64_t*)(Data + offset + 1) << "\n";
                    drawblackjackEntity_int64_t_(&blackjack, (int64_t *)(Data + offset + 1));
                    offset += 1 + sizeof(int64_t);
                    break;
                case 1:
                    out << "PASS " << *(int64_t*)(Data + offset + 1) << "\n";
                    passblackjackEntity_int64_t_(&blackjack, (int64_t *)(Data + offset + 1));
                    offset += 1 + sizeof(int64_t);
                    break;
            }
        }
    } catch (Blackjack::BlackjackException) {
        return 0;    
    }
    return 0;
}

#ifndef FUZZING
int main(int argc, char **argv) {
    std::ifstream file(argv[1]);
    char input[4000];
    file.read(input, 4000);
    LLVMFuzzerTestOneInput(input, 4000);
    std::cout << "DONE" << std::endl; 
    return 0;
}
#endif