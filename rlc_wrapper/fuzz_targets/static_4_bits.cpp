#include <cstdint>
#include <cstring>
#include <iostream>
#include <ostream>
#include <sys/types.h>
#include <fstream>

#include "../../src/blackjack.cpp"

#define RLC_GET_FUNCTION_DECLS
#define RLC_GET_TYPE_DECLS

extern "C" {
    #include "../include/rlc_names.h"
}

#ifndef FUZZING
#define out std::cout
#else
#define out std::ostream(nullptr)
#endif

int64_t consume_bits(const char *Data, int num_bits, int &byte_offset, int &bit_offset) {
    int64_t result = 0;
    int remaining_bits = num_bits;

    while (true) {
        int to_consume_from_current_byte = std::min(remaining_bits, 8 - bit_offset);
        int shift_count = (8 - bit_offset - remaining_bits);
        int mask = ((1u << to_consume_from_current_byte) - 1) << shift_count;
        int data = (*(Data + byte_offset) & mask) >> shift_count;
        result = (result << to_consume_from_current_byte) | data;

        if(remaining_bits >= (8 - bit_offset)) {
            byte_offset ++;
            remaining_bits -= (8 - bit_offset);
            bit_offset = 0;
        } else {
            bit_offset = bit_offset + remaining_bits;
            return result;
        }
    }
}

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
    int64_t ten = 10;
    blackjackblackjackEntity_int64_t_(&blackjack, &ten);

    int byte_offset = 0;
    int bit_offset = 0;
    int input_size = 4;
    uint8_t isDone = false;
    try {
        while(!isDone && byte_offset + 1 + input_size < Size) // we consume at most 1 + sizeof (int) bytes per iteration.
        {
            int64_t input = consume_bits(Data, input_size, byte_offset, bit_offset);
            switch (std::abs(consume_bits(Data, input_size, byte_offset, bit_offset) % 2))
            {
                case 0:
                    out << "DRAW " << input << "\n";
                    drawblackjackEntity_int64_t_(&blackjack, &input);
                    break;
                case 1:
                    out << "PASS " << input << "\n";
                    passblackjackEntity_int64_t_(&blackjack, &input);
                    break;
            }
            is_donebool_blackjackEntity_(&isDone, &blackjack);
        }
    } catch (Blackjack::BlackjackException) {
        Blackjack_deletevoid_int64_t_((int64_t *)(void **)&blackjack.blackjack);
        return 0;    
    }
    if(!isDone)
        Blackjack_deletevoid_int64_t_((int64_t *)(void **)&blackjack.blackjack);
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