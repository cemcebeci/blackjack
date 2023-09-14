#include "src/blackjack.cpp"

int main() {
    Blackjack blackjack(2);

    blackjack.shuffle_deck();
    blackjack.deal();
    blackjack.dump_state();

    blackjack.take_card(0);
    blackjack.take_card(0);
    blackjack.pass(0);
    blackjack.take_card(1);
    blackjack.take_card(1);
    blackjack.take_card(1);
    blackjack.pass(1);
    blackjack.dump_state();

    std::cout << "Winner: " << blackjack.calculate_winner() << "\n";

    return 0;
}