// AVERAGE TIME 
// 0.04868834257125854

#include <iostream>
#include <random>

typedef unsigned char uchar;

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline uchar get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

int main() {
    int C,MX,S;
    std::cin >> C;
    size_t N;
    for (int i = 0; i < C; i++) {
        // get input / seed
        std::cin >> N >> MX >> S;
        random_engine.seed(S);
        // generate array
        uchar* array = new uchar[N+1];
        for (size_t i = 0; i < N; i++) array[i] = get_random(MX);
        // START LOOP
        //Result values
        size_t len_seq = 1;
        size_t start_first = 0;
        size_t start_second = 0;

        // temporary values
        size_t _len;


        const uchar* ARRAY_END = array + N;
        uchar* at_left;
        uchar* at_right;

        // looper pekeren til venstre fra 0 til N i arrayen
        for (at_left = array; at_left < ARRAY_END-1;at_left++) {
            // Looper pekeren til høyre fra peker_venstre + 1 til slutten
            for (at_right = at_left + 1; at_right < ARRAY_END; at_right++) {
                if (*at_left != *at_right) continue;
                _len = 1;
                while (at_right+_len < ARRAY_END) {
                    if ( at_left[_len] != at_right[_len]) break;
                    _len++;
                }
                if (_len > len_seq) {
                    len_seq = _len;
                    start_first = (size_t)(at_left-array);
                    start_second = (size_t)(at_right-array);
                }
            }
        }
        printf("%u %u %u\n",len_seq,start_first,start_second);
        delete[] array;
    }
    return 0;
}