// AVERAGE TIME 
// 0.04868834257125854

#include <iostream>
#include <random>
#include <omp.h>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline unsigned char get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

#define ALIGN 64

int main() {
    int C,MX,S;
    std::cin >> C;
    unsigned int N;
    for (int i = 0; i < C; i++) {
        // get input / seed
        std::cin >> N >> MX >> S;
        random_engine.seed(S);
        // generate array
        unsigned char array[N+1] __attribute__((aligned(ALIGN )));;
        for (unsigned int i = 0; i < N; i++) array[i] = get_random(MX);
        // START LOOP
        //Result values
        unsigned int len_seq = 1;
        unsigned int start_first = 0;
        unsigned int start_second = 0;

        // temporary values
        unsigned int _len;


        const unsigned int ARRAY_END = N;
        unsigned int at_left;
        unsigned int at_right;

        // looper pekeren til venstre fra 0 til N i arrayen
        for (at_left = 0; at_left < ARRAY_END-1;at_left++) {
            // Looper pekeren til høyre fra peker_venstre + 1 til slutten
            for (at_right = at_left + 1; at_right < ARRAY_END; at_right++) {
                if (array[at_left] != array[at_right]) continue;
                _len = 1;
                while (at_right+_len < ARRAY_END) {
                    if ( array[at_left + _len] != array[at_right +_len]) break;
                    _len++;
                }
                if (_len > len_seq) {
                    len_seq = _len;
                    start_first = at_left;
                    start_second = at_right;
                }
            }
        }
        printf("%u %u %u\n",len_seq,start_first,start_second);
        //delete[] array;
    }
    return 0;
}