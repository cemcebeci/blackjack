#include <cstdint>

#define RLC_GET_FUNCTION_DECLS
#define RLC_GET_TYPE_DECLS

extern "C" {
    #include "include/rlc_names.h"
}

int main() {
    blackjackEntity blackjack;
    int64_t two = 2;
    blackjackblackjackEntity_int64_t_(&blackjack, &two);

    int64_t player_0 = 0;
    int64_t player_1 = 1;
    passblackjackEntity_int64_t_(&blackjack, &player_0);
    passblackjackEntity_int64_t_(&blackjack, &player_1); 
}