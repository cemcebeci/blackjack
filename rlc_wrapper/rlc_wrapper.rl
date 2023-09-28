ext fun Blackjack_new(Int player_count) -> Int
ext fun Blackjack_delete(Int address)
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
        let passed = false
        let index_among_valid_players : Int
        actions:
            act draw(Int index1) {
                index1 < (num_players - pass_count)
            }
            index_among_valid_players = index1

            act pass(Int index2) {
                index2 < (num_players - pass_count)
            }
            index_among_valid_players = index2
            passed = true

        if index_among_valid_players >= num_players - pass_count:
            index_among_valid_players = -1
        
        let i = 0
        let actual_player_index = -1
        while(i <= index_among_valid_players):
            actual_player_index = actual_player_index + 1
            while has_passed[actual_player_index] != 0:
                actual_player_index = actual_player_index + 1
            i  = i + 1
        
        if passed:
            Blackjack_pass(blackjack, actual_player_index)
            has_passed[actual_player_index] = 1
            pass_count = pass_count + 1
        else:
            Blackjack_draw(blackjack, actual_player_index)
    
    Blackjack_dump_state(blackjack)
    Blackjack_delete(blackjack)

fun main() -> Int:
    let blackjack = blackjack(2)
    blackjack.draw(0)
    blackjack.draw(0)
    blackjack.draw(1)
    blackjack.pass(0)
    blackjack.draw(0)
    blackjack.draw(0)
    blackjack.pass(0)
    return 0
