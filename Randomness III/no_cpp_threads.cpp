#include <stdio.h>
#include <pthread.h>

// For lagged fib-generator
constexpr unsigned int word_size = 24;
constexpr unsigned int short_lag = 10;
constexpr unsigned int long_lag = 24;
constexpr unsigned int MOD24 = 16777216;
constexpr unsigned int MOD24AND = MOD24-1;
constexpr unsigned long __n = (word_size + 31) / 32;

// For linear-congruential-generator
unsigned int* rand_array[long_lag];
constexpr unsigned int lcg_a = 40014u;
constexpr unsigned int lcg_m = 2147483563u;
constexpr unsigned int default_seed = 19780503U;

struct RandEngine {
    unsigned int _M_x[long_lag];
    unsigned int _M_carry;
    unsigned long _M_p;
    unsigned long long int lcg_value;
};

inline unsigned int LCG(RandEngine& engine) {
    engine.lcg_value = (lcg_a*engine.lcg_value)%lcg_m;
    return (unsigned int)engine.lcg_value;
}


inline void seed(RandEngine& engine, unsigned int val) {
    engine.lcg_value = val;
    for (unsigned long __i = 0; __i < long_lag; ++__i)   {
        engine._M_x[__i] = LCG(engine) & MOD24AND;
    }
    engine._M_carry = (engine._M_x[long_lag - 1] == 0) ? 1 : 0;
    engine._M_p = 0;
}

inline unsigned int get_random(RandEngine& engine) {
    // Derive short lag index from current index.
    long __ps = engine._M_p - short_lag;
    if (__ps < 0)
    __ps += long_lag;

    // Calculate new x(i) without overflow or division.
    // NB: Thanks to the requirements for _unsigned intType, _M_x[engine._M_p] + _M_carry
    // cannot overflow.
    unsigned int __xi; // MOD2^24
    if (engine._M_x[__ps] >= engine._M_x[engine._M_p] + engine._M_carry) {
        __xi = engine._M_x[__ps] - engine._M_x[engine._M_p] - engine._M_carry;
        engine._M_carry = 0;
    } else {
        __xi = (MOD24 - engine._M_x[engine._M_p] - engine._M_carry + engine._M_x[__ps]);
        engine._M_carry = 1;
    }
    engine._M_x[engine._M_p] = __xi & MOD24AND;

    // Adjust current index to loop around in ring buffer.
    if (++engine._M_p >= long_lag) engine._M_p = 0;
    return __xi;
}

constexpr unsigned int range = 16777216U;

inline unsigned char random(RandEngine& engine,unsigned int to) {
  float fTmp = static_cast<float>(get_random(engine)) / range;
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

inline void getint(unsigned long long& num) {
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

inline bool memcmp(unsigned char* m1, unsigned char* m2, unsigned int size) {
    for (unsigned int i = 0; i < size; i++) {
        if (m1[i] != m2[i]) return true;
    }
    return false;
}

void* magic(void* args) {
    unsigned long long int* ARGS = (unsigned long long int*)args;
    unsigned int N = (unsigned int)ARGS[0];
    unsigned int MX = (unsigned int)ARGS[1];
    unsigned int S = (unsigned int)ARGS[2];
    unsigned int* RESULT = (unsigned int*)ARGS[3];
    unsigned int N2 = 2*N;
    RandEngine engine;

    seed(engine,S);

    unsigned char* array = new unsigned char[N2];
    unsigned char* array2 = &array[N];
    unsigned int at = 0;
    unsigned int count = 0;

    for (unsigned int i = 0; i < N2; i++) {
        array[i] = random(engine,MX);
    }
    count = N2;

    while (memcmp(array,array2,N)) {
        array[at] = random(engine,MX);
        count++;
        at++;
        if (at >= N2) at = 0;
    }

    RESULT[0] = count;
    for (unsigned int i = 0; i < N; i++) {
         if (--at > N2) at = N2-1;
         RESULT[N-i] = array[at];
    }

    delete[] array;
    pthread_exit(NULL);
}

int main() {
    unsigned int C;
    getint(C);

    pthread_t* threads = new pthread_t[C];
    unsigned int** results = new unsigned int*[C];

    unsigned long long int args[C][4];
    for (unsigned int i = 0; i < C; i++) {
        getint(args[i][0]); // N
        getint(args[i][1]); // MX
        getint(args[i][2]); // S
        results[i] = new unsigned int[args[i][0]+1]; 
        args[i][3] = (unsigned long long)results[i];
        pthread_create(&threads[i],NULL,magic,(void *)args[i]);
    }

    for (unsigned int i = 0; i < C; i++) {
        pthread_join(threads[i],NULL);
        printf("%u",results[i][0]);
        for (unsigned int k = 1; k <= args[i][0]; k++) {
            printf(" %u",results[i][k]);
        }
        printf("\n");
    }
}

