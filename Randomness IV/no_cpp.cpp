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
constexpr unsigned char TONUM = 0x0f;

// inline void getint(unsigned int& num) {
//     num = 0;
//     unsigned char c = getchar();
//     while (c < ZERO || c > NINE ) c = getchar();
//     while (c >= ZERO && c <= NINE) {
//         num  = num*10 + (c & TONUM);
//         c = getchar();
//     }
// }

inline void getint(unsigned int& num) {
    num = 0;
    unsigned char* number = new unsigned char[10];
    unsigned int radix = 0;
    unsigned char c = getchar();
    while (c < ZERO || c > NINE ) c = getchar();
    while (c >= ZERO && c <= NINE) {
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
    unsigned int C,MX,S;
    getint(C);
    unsigned int N;
    for (unsigned int i = 0; i < C; i++) {
        // get input / seed
        getint(N);
        getint(MX);
        getint(S);
        seed(S);
        // generate array
        unsigned char* array = new unsigned char[N+1];
        for (unsigned int i = 0; i < N; i++) array[i] = random(MX);
        // START LOOP
        //Result values
        unsigned int len_seq = 1;
        unsigned int start_first = 0;
        unsigned int start_second = 0;

        // temporary values
        unsigned int _len;


        const unsigned char* ARRAY_END = array + N;
        unsigned char* at_left;
        unsigned char* at_right;

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
                    start_first = (unsigned int)(at_left-array);
                    start_second = (unsigned int)(at_right-array);
                }
            }
        }
        printf("%u %u %u\n",len_seq,start_first,start_second);
        delete[] array;
    }
    return 0;
}