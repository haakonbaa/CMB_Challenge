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

inline unsigned int random(RandEngine& engine,unsigned int from, unsigned int to) {
  float fTmp = static_cast<float>(get_random(engine)) / range;
  return (fTmp * (to - from + 1)) + from;
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

void* magic(void* args) {
    // Get arguments of chase
    unsigned long long* ARGS = (unsigned long long*)args;

    const unsigned int N = (unsigned int)ARGS[0];
    const unsigned int MIN = (unsigned int)ARGS[1];
    const unsigned int MAX = (unsigned int)ARGS[2];
    const unsigned int S = (unsigned int)ARGS[3];
    printf("%u %u %u %u\n",N,MIN,MAX,S);
    unsigned long long& RESULT = ARGS[4];

    RandEngine engine;
    seed(engine,S);

    unsigned int* array = new unsigned int[N+2];
    for (unsigned int j = 1; j <= N; j++) {
        array[j] = random(engine,MIN,MAX);
    }
    array[0] = 0;
    array[N+1] = 0;

    // initialize variables
    unsigned int max_size;
    unsigned int v;
    unsigned int atl;
    unsigned int atr;
    unsigned int _size;
    unsigned int x;
    unsigned int stop;

    max_size = N*MIN;
    stop = MIN + (MAX-MIN)/2;
    for (x = 1; x <= N; x++) {
        v = array[x];
        if ( v < stop ) {
            atr = x+1;
            atl = x-1;
            while (array[atr] >= v) atr++;
            while (array[atl] >= v) atl--;
            _size = (v)*(atr-atl-1);
            if (_size > max_size) max_size = _size;
        }
    }
    // store value;
    RESULT = (unsigned long long)max_size;
    delete[] array;
    pthread_exit(NULL);
}

int main() {
    unsigned int C,S;
    getint(C);
    getint(S);


    pthread_t* threads = new pthread_t[C];
    unsigned long long args[C][5]; // N, MIN , MAX, S, SAVE

    for (unsigned int i = 0; i < C; i++) {
        unsigned long long& N = args[i][0];
        unsigned long long& MIN = args[i][1];
        unsigned long long& MAX = args[i][2];
        args[i][3] = S;

        getint(N); // N
        getint(MIN); // MIN
        getint(MAX); // MAX

        pthread_create(&threads[i],NULL,magic,(void *)args[i]);
    }
    for (unsigned int i = 0; i < C; i++) {
        pthread_join(threads[i],NULL);
        printf("%llu\n",args[i][4]);
    }
}

