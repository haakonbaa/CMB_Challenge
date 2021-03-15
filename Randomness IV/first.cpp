#include <iostream>
#include <random>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

/* tar inn en array, to pointere og en lengde. Her sjekkes
 * om pi og p2 peker på starten av en LIK sekvens med
 * lengde len.
 */
inline bool compareseq(unsigned char* start,unsigned char* p1, unsigned char* p2, int len) {
    for (int i = 0; i < len; i++) {
        if ( *(p1+i) != *(p2+i) ) return false;
    }
    return true;
}

inline void magic(size_t N, int MX, int S) {
    //int MX,S;
    //size_t N;
    unsigned char* arr;
    unsigned char* arrEnd;

    random_engine.seed(S);

    arr = new unsigned char[N]; // const
    arrEnd = arr + N;           // const
    for (size_t j = 0; j < N;j++) {
        arr[j] = (unsigned char)get_random(MX);
    }

    unsigned char* at;
    unsigned char* seqat;
    // For alle mulige M, starter fra største M
    for (int M = N-1; M > 0; M--) {
        // for alle M-lange sekvenser, start fra venstre:
        for (at = arr; at < arrEnd - M + 1; at++) {
            // finn en match til sekvensen som starter på 'at'
            // og er M lang. start søket etter 'at'
            for (seqat = at+1; seqat < arrEnd - M + 1; seqat++) {
                if (compareseq(arr,at,seqat,M)) {
                    std::cout << M << ' ' << at - arr << ' ' << seqat - arr << '\n';
                    return;
                }
            }
        }
    }
}

int main() {
    int C;
    std::cin >> C;
    size_t* arr_N = new size_t[C];
    int* arr_MX = new int[C];
    int* arr_S = new int[C];
    for (int i = 0; i < C; i++) {
        std::cin >> arr_N[i] >> arr_MX[i] >> arr_S[i];
    }
    for (int i = 0; i < C; i++) {
        magic(arr_N[i], arr_MX[i], arr_S[i]);
    }
    return 0;
}