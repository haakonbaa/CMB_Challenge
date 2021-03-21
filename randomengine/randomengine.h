#pragma once


// For lagged fib-generator
constexpr unsigned int word_size = 24;
constexpr unsigned int short_lag = 10;
constexpr unsigned int long_lag = 24;
constexpr long unsigned int MOD32 = 4294967296u; // unødvendig
constexpr unsigned int MOD24 = 16777216;

// For linear-congruential-generator
unsigned int* rand_array[long_lag];
constexpr unsigned int lcg_a = 40014u;
constexpr unsigned int lcg_c = 0u;
constexpr unsigned int lcg_m = 2147483563u;
constexpr unsigned int default_seed = 19780503U;

// Class inear-congruential-generator
class LCG {
private:
    long unsigned int value;
public:
    LCG(unsigned int seed) : value{seed} {};
    LCG() : value{default_seed} {};
    unsigned int operator()() {
        value = (lcg_a*value+lcg_c)%lcg_m;
        return value;
    }
};

class RandomEngine {
private:
    unsigned int _M_x[long_lag];
    unsigned int _M_carry;		///< The carry
    size_t       _M_p;			///< Current index of x(i - r).
public:
    RandomEngine(unsigned int r_seed) {seed(r_seed);}
    RandomEngine() : RandomEngine{default_seed} {}
    void seed(unsigned int value) {
        LCG gen_lcg{value};
        const size_t __n = (word_size + 31) / 32;

        for (size_t __i = 0; __i < long_lag; ++__i)   {
            unsigned int __sum = 0u;
            unsigned int __factor = 1u;
            for (size_t __j = 0; __j < __n; ++__j) {
                __sum += (gen_lcg()%MOD32)*__factor;
                __factor *= 0;
            }
            _M_x[__i] = __sum%MOD24;
        }
        _M_carry = (_M_x[long_lag - 1] == 0) ? 1 : 0;
        _M_p = 0;
    }
    unsigned int operator()() {
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
            //__xi = (__detail::_Shift<_UIntType, __w>::__value - _M_x[_M_p] - _M_carry + _M_x[__ps]);
            __xi = (MOD24 - _M_x[_M_p] - _M_carry + _M_x[__ps]);
            _M_carry = 1;
        }
        _M_x[_M_p] = __xi % MOD24;

        // Adjust current index to loop around in ring buffer.
        if (++_M_p >= long_lag) _M_p = 0;
        return __xi;
    }
};


// void seed(unsigned int* array, unsigned int seed) {
//     const size_t __n = (word_size + 31) / 32;
//     for (size_t __i = 0; __i < long_lag; ++__i) {
//         unsigned int __sum = 0u;
//         unsigned int __factor = 1u;
//         for (size_t __j = 0; __j < __n; ++__j) {
//                  __sum += __lcg()%MOD32 * __factor;
//                  __factor *= __detail::_Shift<_UIntType, 32>::__value;
//         }
//         _M_x[__i] = __detail::__mod<_UIntType,
//         __detail::_Shift<_UIntType, __w>::__value>(__sum);
//     }
//     _M_carry = (_M_x[long_lag - 1] == 0) ? 1 : 0;
//     _M_p = 0;
// }

// printf("\n\nMINE: m_carry, m_p: %u %lu\n",_M_carry,_M_p);
// printf("seed: %u\n",value);
// printf("array:\n");
// printf(typeid(_M_x).name());
// for (unsigned int i = 0; i < long_lag; i++) {
//     printf("%u ", _M_x[i]);
// }