#include <stdio.h>

// For lagged fib-generator
constexpr unsigned int word_size = 24;
constexpr unsigned int short_lag = 10;
constexpr unsigned int long_lag = 24;
constexpr unsigned int MOD24 = 16777216;
constexpr unsigned int MOD24AND = MOD24-1;
constexpr unsigned long __n = (word_size + 31) / 32;

unsigned int _M_x[long_lag];
unsigned int _M_carry;		///< The carry
unsigned long _M_p;			///< Current index of x(i - r).

// For linear-congruential-generator
unsigned int* rand_array[long_lag];
constexpr unsigned int lcg_a = 40014u;
constexpr unsigned int lcg_m = 2147483563u;
constexpr unsigned int default_seed = 19780503U;
 
unsigned long long int lcg_value = default_seed; // må ha minst 8 bytes! (for en eller annen grunn) 

inline unsigned int LCG() {
    lcg_value = (lcg_a*lcg_value)%lcg_m;
    return (unsigned int)lcg_value;
}

inline void seed(unsigned int val) {
    lcg_value = val;
    for (unsigned long __i = 0; __i < long_lag; ++__i)   {
        _M_x[__i] = LCG() & MOD24AND;
    }
    _M_carry = (_M_x[long_lag - 1] == 0) ? 1 : 0;
    _M_p = 0;
}

inline unsigned int get_random() {
    // Derive short lag index from current index.
    long __ps = _M_p - short_lag;
    if (__ps < 0)
    __ps += long_lag;

    // Calculate new x(i) without overflow or division.
    // NB: Thanks to the requirements for _UIntType, _M_x[_M_p] + _M_carry
    // cannot overflow.
    unsigned int __xi; // MOD2^24
    if (_M_x[__ps] >= _M_x[_M_p] + _M_carry) {
        __xi = _M_x[__ps] - _M_x[_M_p] - _M_carry;
        _M_carry = 0;
    } else {
        __xi = (MOD24 - _M_x[_M_p] - _M_carry + _M_x[__ps]);
        _M_carry = 1;
    }
    _M_x[_M_p] = __xi & MOD24AND;

    // Adjust current index to loop around in ring buffer.
    if (++_M_p >= long_lag) _M_p = 0;
    return __xi;
}

constexpr unsigned int range = 16777216U;

inline unsigned char random(int to) {
    float fTmp = (float)(get_random())/range;
    return (fTmp * (to + 1));
}

constexpr unsigned int BASE10[10] = {
    0x00000001, 0x0000000a,
    0x00000064, 0x000003e8,
    0x00002710, 0x000186a0,
    0x000f4240, 0x00989680,
    0x05f5e100, 0x3b9aca00
};

constexpr unsigned char ZERO = '0';
constexpr unsigned char NINE = '9';
constexpr unsigned char TONUM = 0x0f; // ascii-verdi til num


inline void getint(unsigned int& num) {
    num = 0;
    unsigned char c = getchar();
    while (c < ZERO || c > NINE ) c = getchar();
    while (c >= ZERO && c <= NINE) {
        num  = num*10 + (c & TONUM);
        c = getchar();
    }
}

constexpr int MEMORY = 1000000000; // absolutt ikke bra :) 

inline bool notIsSequence(unsigned char* arr1, unsigned char* arr2, const unsigned int& len ) {
    unsigned char* tmp = arr2;
    while (arr1 < tmp) {
        if (*arr1 != *arr2) return true;
        ++arr1;
        ++arr2;
    }
    return false;
}

inline void magic(unsigned int N, unsigned int MX, unsigned int S) {
    seed(S);
    unsigned int count = 0;
    unsigned char* arr = new unsigned char[MEMORY];
    unsigned char* at1 = arr;
    unsigned char* at2 = arr + N;
    unsigned char* put = arr + 2*N;

    for (unsigned int i = 0; i < 2*N; i++) {
        arr[i] = random(MX);
    }
    count = 2*N;

    while (notIsSequence(&arr[count-N-N],&arr[count-N],N)) {
        *put = random(MX);
        ++at1; ++at2; ++put;
        ++count;
    }

    printf("%u",count);
    for (unsigned int i = 0; i < N; i++) {
        printf(" %u", arr[count-N+i]);
    }
    printf("\n");

    delete[] arr;
}

int main() {
    unsigned int C;
    getint(C);
    unsigned int N, MX, S;
    for (unsigned int c = 0; c < C; c++) {
        getint(N);
        getint(MX);
        getint(S);
        magic(N,MX,S);
    }
    return 0;
}