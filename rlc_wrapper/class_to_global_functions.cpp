#include "../src/blackjack.cpp"
#include <cstdint>
#include <cstdio>
#include <iostream>

#define RLC_GET_FUNCTION_DECLS
#define RLC_GET_TYPE_DECLS

extern "C" {
    #include "include/rlc_names.h"
}

extern "C" void Blackjack_newint64_t_int64_t_(int64_t * __result, int64_t * player_count) {
    *__result = (int64_t) (void *)new Blackjack(*player_count);
}

extern "C" void Blackjack_shufflevoid_int64_t_(int64_t *address) {
    ((Blackjack *)(void *)*address)->shuffle_deck();
}

extern "C" void Blackjack_dealvoid_int64_t_(int64_t *address) {
    ((Blackjack *)(void *)*address)->deal();
}

extern "C" void Blackjack_drawvoid_int64_t_int64_t_(int64_t * address, int64_t * player) {
    ((Blackjack *)(void *)*address)->take_card(*player);
}

extern "C" void Blackjack_passvoid_int64_t_int64_t_(int64_t * address, int64_t * player) {
    ((Blackjack *)(void *)*address)->pass(*player);
}

extern "C" void Blackjack_dump_statevoid_int64_t_(int64_t * address){
    ((Blackjack *)(void *)*address)->dump_state();
}

extern "C" void Blackjack_calculate_winnerint64_t_int64_t_(int64_t * __result, int64_t * address) {
    *__result = ((Blackjack *)(void *)*address)->calculate_winner();
}