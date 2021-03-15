#include <iostream>
#include <random>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

int main() {
    int M,MX,S;
    size_t index = 0;
    int* arr;
    int* arrcmp;

    std::cin >> M >> MX >> S;
    arr = new int[M];
    arrcmp = new int[M];
    random_engine.seed(S);

    for (;index<M;index++) {
        arr[index] = get_random(MX);
    }

    while (true) {
        
    }
    std::cout << index;
    return 0;
}