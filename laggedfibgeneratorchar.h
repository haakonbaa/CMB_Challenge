// For lagged fib-generator
constexpr unsigned char word_size = 8;
constexpr unsigned char short_lag = 10;
constexpr unsigned char long_lag = 24;

unsigned char _M_x[long_lag];
unsigned char _M_carry;		///< The carry
unsigned char _M_p;			///< Current index of x(i - r).

// For linear-congruential-generator
unsigned char* rand_array[long_lag];
constexpr unsigned char lcg_a = 78u;
constexpr unsigned char lcg_m = 171u;
constexpr unsigned char default_seed = 151u;
constexpr unsigned int MOD8 = 256;
 
unsigned char lcg_value = default_seed; // må ha minst 8 bytes! (for en eller annen grunn) 

inline unsigned char LCG() {
    lcg_value = (lcg_a*lcg_value)%lcg_m;
    return (unsigned char)lcg_value;
}

inline void seed(unsigned int val) {
    lcg_value = val;
    for (unsigned long __i = 0; __i < long_lag; ++__i)   {
        _M_x[__i] = LCG();
    }
    _M_carry = (_M_x[long_lag - 1] == 0) ? 1 : 0;
    _M_p = 0;
}

inline unsigned char get_random() {
    // Derive short lag index from current index.
    long __ps = _M_p - short_lag;
    if (__ps < 0)
    __ps += long_lag;

    // Calculate new x(i) without overflow or division.
    // NB: Thanks to the requirements for _UIntType, _M_x[_M_p] + _M_carry
    // cannot overflow.
    unsigned char __xi; // MOD2^24
    if (_M_x[__ps] >= _M_x[_M_p] + _M_carry) {
        __xi = _M_x[__ps] - _M_x[_M_p] - _M_carry;
        _M_carry = 0;
    } else {
        __xi = (-_M_x[_M_p] - _M_carry + _M_x[__ps]);
        _M_carry = 1;
    }
    _M_x[_M_p] = __xi;

    // Adjust current index to loop around in ring buffer.
    if (++_M_p >= long_lag) _M_p = 0;
    return __xi;
}