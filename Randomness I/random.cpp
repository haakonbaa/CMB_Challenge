#include <iostream>
#include <random>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int from, int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to - from + 1)) + from;
}

int main() {
    int N,S,MX,rnum;
    int last = -1;
    int reps = 0;
    int count = 0;
    std::cin >> N >> MX >> S;
    random_engine.seed(S);
    while (true) {
        rnum = get_random(0,MX);
        rnum == last ? reps++:(reps=1);
        last = rnum;
        count++;
        if (reps == N) break;
    }
    std::cout << count << ' ' << last << '\n';
    return 0;
}