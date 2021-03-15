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
    int similar = 0;
    size_t index = 0;
    int* arr;

    std::cin >> M >> MX >> S;
    arr = new int[M];
    random_engine.seed(S);

    for (;index<M;index++) {
        arr[index] = get_random(MX);
    }

    //pre check
    for (size_t i = 1; i < M; i++) {
        (arr[i] == arr[i-1]) ? similar++ : similar = 0;
    }

    while (true) {
        (get_random(MX) == arr[similar]) ? similar++:similar=0;
        index++;
        if (similar == M) break;
    }
    std::cout << index;
    return 0;
}