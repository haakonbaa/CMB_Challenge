#include <iostream>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <cstring>

typedef unsigned int uint;

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

unsigned int get_random(unsigned int from, unsigned int to) {
  float fTmp = static_cast<float>(random_engine()) / random_range;
  return (fTmp * (to - from + 1)) + from;
}

int main() {
    std::cin.sync_with_stdio(false);
    unsigned int C, S;
    std::cin >> C >> S;
    random_engine.seed(S);

    unsigned int N, MIN, MAX;
    unsigned int max_size;
    for (unsigned int a = 0; a < C; a++) {
        std::cin >> N >> MIN >> MAX;

        uint* array = new uint[N];
        uint* arraySort = new uint[N];
        max_size = N*MIN;

        unsigned int rep;
        unsigned int max_rep;
        unsigned int value;
        unsigned int _size;

        for (unsigned int j = 0; j < N; j++) {
            array[j] = get_random(MIN,MAX);
        }

        memcpy(arraySort,array,N*sizeof(uint));
        std::sort(arraySort,arraySort+N);

        for (unsigned int i = 1; i < N; i++) {
            rep = 0;
            max_rep = 0;
            value = arraySort[i];
            if (value == arraySort[i-1]) continue;
            for (unsigned int x = 0; x < N; x++) {
                if (array[x] >= value) {
                    rep++;
                } else {
                    if ( rep > max_rep ) max_rep = rep;
                    rep = 0;
                }
            }
            _size = max_rep*value;
            if (_size > max_size) max_size = _size;
        }
        std::cout << max_size << std::endl;
        delete[] array;
    }
}

