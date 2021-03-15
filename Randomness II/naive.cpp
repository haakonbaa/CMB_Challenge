#include <iostream>
#include <random>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

inline bool compare(int* arr1, int* arr2,int M) {
    for (size_t i = 0; i < M; i++) {
        if (arr1[i] != arr2[i]) return false;
    }
    return true;
}

// subtraher med 1 før du setter in len
inline void pushback(int* arr, int n, int len) {
    for (size_t i = 0; i < len; i++) {
        arr[i] = arr[i+1];
    }
    arr[len] = n;
}

int main() {
    int M,MX,S;
    std::cin >> M >> MX >> S;
    int* arr = new int[M];
    int* cmp = new int[M];
    random_engine.seed(S);
    size_t index = 0;
    int rand;
    for (;index<M;index++) {
        rand = get_random(MX);
        arr[index] = rand;
        cmp[index] = rand;
    }
    while (true) {
        pushback(cmp,get_random(MX),M-1);
        index++;
        if (compare(arr,cmp,M)) {break;std::cout << "done!\n";}
    }
    std::cout << index;
    return 0;
}