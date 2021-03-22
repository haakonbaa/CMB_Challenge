#include <stdio.h>
#include <iostream>

#include "laggedfibgeneratorui.h"

constexpr unsigned int range = 16777216U;

inline int my_rand(int to) {
    float fTmp = (float)(get_random())/range;
    return (fTmp * (to + 1));
}

int main() {
    unsigned int N,S,MX;
    int rnum;
    int last = -1;
    int reps = 0;
    int count = 0;
    std::cin >> N >> MX >> S;
    seed(S);
    while (true) {
        rnum = my_rand(MX);
        rnum == last ? reps++:(reps=1);
        if (reps == N) break;
        last = rnum;
        count++;
    }
    printf("%d %d\n",++count,last);
    return 0;
}