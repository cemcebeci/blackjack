#include "../src/blackjack.cpp"

extern "C" Blackjack *Blackjack_newint64_t_int64_t_(int *num_players) {
    return new Blackjack(*num_players);
}

extern "C" void Blackjack_shufflevoid_int64_t_(Blackjack **blackjack) {
    (*blackjack)->shuffle_deck();
}

extern "C" void Blackjack_dealvoid_int64_t_(Blackjack **blackjack) {
    (*blackjack)->deal();
}

extern "C" void Blackjack_drawvoid_int64_t_int64_t_(Blackjack **blackjack, int *player) {
    (*blackjack)->take_card(*player);
}

extern "C" void Blackjack_passvoid_int64_t_int64_t_(Blackjack **blackjack, int *player) {
    (*blackjack)->pass(*player);
}

extern "C" void Blackjack_dump_statevoid_int64_t_(Blackjack **blackjack) {
    (* blackjack)->dump_state();
}

extern "C" int Blackjack_calculate_winnerint64_t_int64_t_(Blackjack **blackjack) {
    return (* blackjack)->calculate_winner();
}