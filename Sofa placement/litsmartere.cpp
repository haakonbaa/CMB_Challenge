#include <iostream>
#include <random>

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
    unsigned int v;
    unsigned int atl;
    unsigned int atr;
    unsigned int _size;
    unsigned int x;
    unsigned int stop;
    for (unsigned int a = 0; a < C; a++) {
        std::cin >> N >> MIN >> MAX;
        uint* array = new uint[N+2];
        for (unsigned int j = 1; j <= N; j++) {
            array[j] = get_random(MIN,MAX);
        }
        array[0] = 0;
        array[N+1] = 0;
        max_size = N*MIN;
        stop = MIN + (MAX-MIN)/2;
        for (x = 1; x <= N; x++) {
            v = array[x];
            if ( v < stop ) {
                atr = x+1;
                atl = x-1;
                while (array[atr] >= v) atr++;
                while (array[atl] >= v) atl--;
                _size = (v)*(atr-atl-1);
                if (_size > max_size) max_size = _size;
            }
        }
        std::cout << max_size << std::endl;
        delete[] array;
    }
}

