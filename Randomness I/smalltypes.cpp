#include <random>
#include <iostream>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

int main() {
    int S,rnum,MX;
    unsigned char N;
    int last = -1;
    unsigned char reps = 0x00;
    unsigned int count = 0;
    unsigned int Nint;
    std::cin >> Nint >> MX >> S;
    N = (unsigned char)Nint;
    random_engine.seed(S);
    while (true) {
        count++;
        rnum = get_random(MX);
        rnum == last ? reps++:(reps=0x01);
        if (reps == N) break;
        last = rnum;
    }
    std::cout << count << ' ' << last << '\n';
    return 0;
}