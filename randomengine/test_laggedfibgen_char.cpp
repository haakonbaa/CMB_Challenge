#include <random>
#include <iostream>
#include <laggedfibgeneratorchar.h>

std::subtract_with_carry_engine<unsigned char, 8, 10, 24> random_engine;

int main() {
    unsigned int SEED = 321u;
    seed(SEED);
    random_engine.seed(SEED);

    for (int i = 0; i < 10000000; i++) {
        if (random_engine() == get_random()) continue;
        printf("TEST FAILED!\n");
        break;
    }

    return 0;
}