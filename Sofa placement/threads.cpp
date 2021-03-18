#include <iostream>
#include <random>
#include <pthread.h>

typedef unsigned int uint;

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

unsigned int get_random(unsigned int from, unsigned int to) {
  float fTmp = static_cast<float>(random_engine()) / random_range;
  return (fTmp * (to - from + 1)) + from;
}

void* magic(void *data) {
    unsigned int* args = (unsigned int*)data;

    unsigned int N = args[0];
    unsigned int MIN = args[1];
    unsigned int MAX = args[2];

    unsigned int max_size;
    unsigned int v;
    unsigned int atl;
    unsigned int atr;
    unsigned int _size;
    unsigned int x;

    unsigned int* array = new uint[N+2];
    for (unsigned int j = 1; j <= N; j++) {
        array[j] = get_random(MIN,MAX);
    }
    array[0] = 0;
    array[N+1] = 0;
    max_size = N*MIN;
    for (x = 1; x <= N; x++) {
        v = array[x];
        atr = x+1;
        atl = x-1;
        while (array[atr] >= v) atr++;
        while (array[atl] >= v) atl--;
        _size = (v)*(atr-atl-1);
        if (_size > max_size) max_size = _size;
    }
    args[3] = max_size;
    delete[] array;
    pthread_exit(NULL);
}

int main() {
    std::cin.sync_with_stdio(false);
    unsigned int C, S;
    std::cin >> C >> S;
    random_engine.seed(S);

    pthread_t* threads = new pthread_t[C];
    unsigned int* threadData = new unsigned int[4*C];


    unsigned int n, min, max;
    for (unsigned int i = 0; i < C; i++) {
        std::cin >> n >> min >> max;
        threadData[4*i+0] = n;
        threadData[4*i+1] = min;
        threadData[4*i+2] = max;
        pthread_create(&threads[i],NULL,magic,(void *)&threadData[i*4]);
    }
    for (unsigned int i = 0; i < C; i++) {
        std::cout << pthread_join(threads[i],NULL);
    }
    for (unsigned int i = 0; i < C; i++) {
        std::cout << threadData[4*i+3] << '\n';
    }

    delete[] threads;
    delete[] threadData;

    pthread_exit(NULL);
    return 0;
}

