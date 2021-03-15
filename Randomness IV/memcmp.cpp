#include <iostream>
#include <random>
#include <cstring>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline char get_random(int to) {
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
        char* array = new char[N+1];
        for (size_t i = 0; i < N; i++) array[i] = get_random(MX);
        // START LOOP
        //Result values
        int len_seq = 1;
        int start_first = 0;
        int start_second = 0;

        // temporary values
        size_t _len;


        const char* ARRAY_END = array + N;
        const char* at_left;
        const char* at_right;

        // looper pekeren til venstre fra 0 til N i arrayen
        for (at_left = array; at_left < ARRAY_END-1;at_left++) {
            // Looper pekeren til høyre fra peker_venstre + 1 til slutten
            for (at_right = at_left + 1; at_right < ARRAY_END; at_right++) {
                if (strcmp(at_right,at_left) < len_seq) continue;
                len_seq = strcmp(at_right,at_left);
                std::cout << len_seq << '\n';
                start_first = (int)(at_left-array);
                start_second = (int)(at_right-array);
            }
        }
        printf("%u %u %u\n",len_seq,start_first,start_second);
        delete[] array;
    }
    return 0;
}