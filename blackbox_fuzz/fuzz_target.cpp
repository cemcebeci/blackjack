#include "../src/blackjack.cpp"
#include <cstdint>
#include <sys/types.h>

/*
    Blackjack has 4 actions:
        - shuffle_deck()
        - deal()
        - take_card(int player)
        - pass(int player)
    
    We user the first byte to pick the number of players.
    We interpret the rest of fuzz input as a sequence of actions taken. 
    We use a byte to pick an action (because I don't want to deal with bits).
    If that action has an int parameter, we use the next sizeof(int) to pick the input.
*/
extern "C" int LLVMFuzzerTestOneInput(const char *Data, size_t Size) {
    if( Size == 0)
        return 0;
    
    Blackjack game((uint8_t)*Data);
    int offset = 1;

    try {
        while(offset + 1 + sizeof(int) < Size) // we consume at most 1 + sizeof (int) bytes per iteration.
        {
            switch (*(Data + offset) % 4)
            {
                case 0:
                    game.shuffle_deck();
                    offset += 1;
                    break;
                case 1:
                    game.deal();
                    offset += 1;
                    break;
                case 3:
                    game.take_card(*(Data + 1));
                    offset += 1 + sizeof(int);
                    break;
                case 4:
                    game.pass(*(Data + 1));
                    offset += 1 + sizeof(int);
                    break;
            }
        }
    } catch (Blackjack::BlackjackException) {
        return 0;    
    }
    return 0;
}
