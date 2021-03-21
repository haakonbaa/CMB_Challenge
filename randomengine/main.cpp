#include <random>
#include <iostream>
#include <randomengine.h>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;

int main() {
    RandomEngine test{6969420u};
    random_engine.seed(6969420u);

    for (int i = 0; i < 1000; i++) {
        std::cout << random_engine() << ", " << test() << '\n';
    }
    random_engine();
    random_engine();

    //TestClass test;
    // std::cout << "word size: " << test.word_size << '\n';
    // std::cout << "short lag: " << test.short_lag << '\n';
    // std::cout << "long lag : " << test.long_lag << "\n\n";

    // random_engine.seed();
    // random_engine();
    // std::cout << sizeof(unsigned int) << '\n';

    //std::cout << test._M_x[0] << '\n'; 
    return 0;
}

// class TestClass : public std::subtract_with_carry_engine<unsigned int, 24, 10, 24> {
// private:
//     friend class std::subtract_with_carry_engine<unsigned int,24,10,24>;
// public:
//     void print() {std::cout << "Hello World!\n;";}
// };