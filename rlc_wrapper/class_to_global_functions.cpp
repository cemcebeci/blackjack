#include "../src/blackjack.cpp"
#include <cstdint>
#include <cstdio>
#include <iostream>

extern "C" Blackjack *Blackjack_newint64_t_int64_t_(void* _, uint64_t *num_players) {

    //?? Why does this not work?
    // auto ret = new Blackjack(*num_players);
    // std::cout << "ret" << " -> " << ret << std::endl;
    // *retval = ret; 
    // return ret

    //?? But this one does
    return new Blackjack(*num_players);
}

extern "C" void Blackjack_shufflevoid_int64_t_(void* _, Blackjack *blackjack) {
    //? Why does RLC pass a Blackjack* here and not a Blackjack**?
    std::cout << blackjack << std::endl;
    (blackjack)->shuffle_deck();
    std::cout << "SHUFFLE DONE" << std::endl;
}

extern "C" void Blackjack_dealvoid_int64_t_(void* _, Blackjack *blackjack) {
    std::cout << blackjack << std::endl;
    (blackjack)->deal();
    std::cout << "DEAL DONE" << std::endl;
}

extern "C" void Blackjack_drawvoid_int64_t_int64_t_(void* _, Blackjack *blackjack, int *player) {
    (blackjack)->take_card(*player);
    std::cout << "TAKE DONE" << std::endl;
}

extern "C" void Blackjack_passvoid_int64_t_int64_t_(void* _, Blackjack *blackjack, int *player) {
    (blackjack)->pass(*player);
}

extern "C" void Blackjack_dump_statevoid_int64_t_(void* _, Blackjack *blackjack) {
    (blackjack)->dump_state();
}

extern "C" int Blackjack_calculate_winnerint64_t_int64_t_(void* _, Blackjack *blackjack) {
    return (blackjack)->calculate_winner();
}