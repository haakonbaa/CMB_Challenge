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

unsigned long int lcg_value = default_seed;

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