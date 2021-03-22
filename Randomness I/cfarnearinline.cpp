#include <stdio.h>
#include <iostream>

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

inline int random(int to) {
    float fTmp = (float)(get_random())/range;
    return (fTmp * (to + 1));
}

constexpr unsigned int BASE10[12] = {
    0x00000001, 0x0000000a,
    0x00000064, 0x000003e8,
    0x00002710, 0x000186a0,
    0x000f4240, 0x00989680,
    0x05f5e100, 0x3b9aca00,
    0,0
};

constexpr unsigned char SPACE = ' ';
constexpr unsigned char NEWLINE = '\n';
constexpr unsigned char EOL = '\0';
constexpr unsigned char ZERO = '0';

inline void getint(unsigned int& num) {
    num = 0;
    unsigned char* number = new unsigned char[12];
    unsigned int radix = 0;
    unsigned char c = getchar();
    while (c < ZERO) c = getchar();
    while (c >= ZERO && radix < 12) {
        number[radix] = (c-ZERO);
        radix++;
        c = getchar();
    }
    for (unsigned int i = 0; i < radix; i++) {
        num += (number[i])*BASE10[radix-i-1];
    }
    delete[] number;
}

int main() {
    unsigned int N,MX,S;
    int rnum;
    int last = -1;
    int reps = 0;
    int count = 0;
    // getint(N);
    // getint(MX);
    // getint(S);
    //seed(S);
    printf("\nTEST\n");
    N = 2;
    MX = 5;
    for (N = 1; N < 5; N++) {
        for (MX = 1; MX < 12; MX ++) {
            for (S = 1; S < 1000000; S ++) {
                seed(S);
                last = -1;
                reps = 0;
                count = 0;
                while (true) {
                    rnum = random(MX);
                    rnum == last ? reps++:(reps=1);
                    if (reps == N) break;
                    last = rnum;
                    count++;
                }
                //printf("%d %d\n",++count,last);
                if (++count == 921 && last == 4) {
                    std::cout << N << ' ' << MX << ' ' << S << '\n'; 
                    //return 0;
                }
            }
        }
    }
    printf("DONE!\n");
    printf("%d %d\n",++count,last);
    return 0;
}