# Blackjack
`src/blackjack` contains a very simple implementation of blackjack the card game. This implementation implicitly expects the functions to be called in a "scenario". First, the deck should be shuffled. Then, the cards should be dealt. Then, players should one by one pick whether to draw a card or pass. They don't get a choice after they have passed once. This goes on until all players pass, at which point the library can calculate the winner.  

When an illegal game actions is taken, a `require()` call throws a `BlackjackException`. Examples of illegal game actions are:
- A player who already has passed once draws a card.
- A player draws a card when it's not their turn.
- A player passes before the cards are dealt.

The library has a flaw, it doesn't account for what happens when the deck is empty and a player tries to draw a card. We want to be able to discover this flaw using fuzzing.

## blackbox_fuzz
This directory includes a libFuzzer fuzz target that parses the fuzz input as a sequence of blackjack actions. It tries to find a sequence of actions where the blackjack library crashes without throwing a `BlackjackException`.  

`make` builds two binaries, `fuzzer` and `runner`. `fuzzer` runs the libFuzzer binary and `runner` runs fuzz input files, logging what actions they represent.

## rlc_wrapper
This directory includes a version of the blackjack library wrapped in `rlc_wrapper.rl`. All calls to member functions of `Blackjack`, as  well as the constructor and the destructor are wrapped in global functions in `class_to_global_function.cpp`. `rlc_wrapper.rl` passes an integer `address` to these functions, which should be interpreted as a pointer to the `Blackjack` object.  

Then, `fuzz_target.cpp` includes a version of the fuzz target from `blackbox_fuzz` adapted to the functions RLC exposes. This fuzz target does not pick shuffling and dealing cards as actions since these are done in the RLC action `blackjack`. Aside from that, this fuzz target is as black-box as the previous one. We want to be able to make use of RLC's constraints on action sequencing and action inputs to decrease the number of fuzz runs that terminate with a `BlackjackException`.

`make` builds 4 binaries: `c_driver`, `rlc_driver`, `fuzzer` and `runner`. `fuzzer` and `runner` are functionally identical to their counterparts in `blackbox_fuzz`. `c_driver` and `rlc_driver` execute the main functions in `driver.cpp` and `rlc_wrapper.rl` for debugging.