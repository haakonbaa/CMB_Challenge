#include <iostream>
#include <random>

typedef uint8_t int8;
constexpr int MEMORY = 1000000000; // absolutt ikke bra :) 

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

inline bool notIsSequence(int8* const arr1, int8* const arr2, const int& len ) {
    size_t i;
    for (i = 0; i < len; i++) {
        if (arr1[i] != arr2[i]) return true;
    }
    return false; 
}

inline void magic(int N, int MX, int S) {
    random_engine.seed(S);
    size_t count = 0;
    int8* arr = new int8[MEMORY];

    for (int i = 0; i < 2*N; i++) {
        arr[count] = (int8)get_random(MX);
        count++;
    }

    while (notIsSequence(&arr[count-N-N],&arr[count-N],N)) {
        arr[count] = (int8)get_random(MX);
        count++;
    }

    std::cout << count;
    for (size_t i = 0; i < N; i++) {
        printf(" %d", arr[count-N+i]);
    }
    std::cout << '\n';

    delete[] arr;
}

int main() {
    int C;
    std::cin >> C;
    int N, MX, S;
    for (size_t c = 0; c < C; c++) {
        std::cin >> N >> MX >> S;
        magic(N,MX,S);
    }
    return 0;
}

// int main() {
//     int C;
//     std::cin >> C;
//     int* N = new int[C];
//     int* MX = new int[C];
//     int* S = new int[C];
//     for (size_t c = 0; c < C; c++) {
//         std::cin >> N[c] >> MX[c] >> S[c];
//     }
//     for (size_t c = 0; c < C; c++) {
//         magic( N[c], MX[c], S[c]);
//     }

//     return 0;
// }


// inline bool isIn(int8* const array, int8* const sequence, int len ) {
//     size_t i;
//     for (int8* at = array; at < sequence; at++) {
//         i = 0;
//         do {
//             if (at[i] != sequence[i]) break;
//             i++;
//         } while (i < len);
//         if (i == len) {
//             std::cout << "found:\n";
//             for (size_t i = 0; i < len; i++) {
//                 printf("%d ",at[i]);
//             }
//             std::cout << "\n";
//             return false;
//         }
//     }
//     return true;
// }