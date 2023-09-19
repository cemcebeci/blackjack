ext fun Blackjack_new(Int player_count) -> Int
ext fun Blackjack_shuffle(Int address)
ext fun Blackjack_deal(Int address)
ext fun Blackjack_draw(Int address, Int player)
ext fun Blackjack_pass(Int address, Int player)
ext fun Blackjack_dump_state(Int address)
ext fun Blackjack_calculate_winner(Int address) -> Int

act blackjack(Int num_players):
    let blackjack = Blackjack_new(num_players)
    Blackjack_shuffle(blackjack)
    Blackjack_deal(blackjack)

    let pass_count = 0
    let has_passed : Int[10]
    while pass_count < num_players:
        let player = 0
        while player < num_players:
            if !(has_passed[player] == 1):
                actions:
                    act draw(Int p) {p == player}
                    Blackjack_draw(blackjack, p)	

                    act pass(Int p) {p == player}
                    Blackjack_pass(blackjack, p)
                    pass_count = pass_count + 1
                    has_passed[player] = 1
            player = player + 1
    
    Blackjack_dump_state(blackjack)


fun main() -> Int:
    let blackjack = blackjack(2)
    blackjack.draw(0)
    blackjack.draw(1)
    blackjack.pass(0)
    blackjack.draw(1)
    blackjack.draw(1)
    blackjack.pass(1)
    return 0
