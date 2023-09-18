ext fun Blackjack_new(Int player_count) -> Int
ext fun Blackjack_shuffle(Int address)
ext fun Blackjack_deal(Int address)
ext fun Blackjack_draw(Int address, Int player)
ext fun Blackjack_pass(Int address, Int player)
ext fun Blackjack_dump_state(Int address)
ext fun Blackjack_calculate_winner(Int address) -> Int


fun main() -> Int:
    let blackjack = Blackjack_new(2)
    Blackjack_shuffle(blackjack)
    Blackjack_deal(blackjack)
    Blackjack_draw(blackjack, 0)
    Blackjack_draw(blackjack, 1)
    Blackjack_pass(blackjack, 0)
    Blackjack_dump_state(blackjack)
    Blackjack_calculate_winner(blackjack)
    return 0
