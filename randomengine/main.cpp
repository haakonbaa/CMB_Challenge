#include <random>
#include <iostream>
#include <inlinegenerator.h>
#include <Timer.h>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;

int main() {
    unsigned int SEED = 42069;
    seed(SEED);
    random_engine.seed(SEED);
    // test
    for (int i = 0; i < 10000; i++) {
        if (random_engine() == get_random()) continue;
        std::cout << "TEST FAILED!\n";
        break;
    }

    return 0;
}