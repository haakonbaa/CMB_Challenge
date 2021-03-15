#include <stdio.h>
#include <random>

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

inline int get_random(int to) {
    float fTmp = static_cast<float>(random_engine()) / random_range;
    return (fTmp * (to + 1));
}

constexpr unsigned int MOD = 0x000000ff;

int main() {
    int S,MX,N;
    unsigned int count = 0;
    int rep;
    if (scanf("%d%d%d",&N,&MX,&S) != 3) return 0;
    random_engine.seed(S);
    int* arr = new int[N] {};
    int i;
    while (true) {
        for (i = 0; i < N; i++) arr[i] = get_random(MX);
        count += N;
        rep = 0;
        for (i = 1; i < N; i++) {
            if (arr[i] == arr[0])
                if (i == N-1)
                    goto jump;
                continue;
            break;
        }
    }
jump:
    printf("%d %d",count-N+i+1,arr[i]);
    return 0;
}

// printf bruker mindre energi, ikke tid