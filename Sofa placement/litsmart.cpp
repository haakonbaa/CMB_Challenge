#include <iostream>
#include <random>

#include <chrono>
#include <iostream>

class  Timer {
public:
    Timer(){
        start = std::chrono::system_clock::now();
    }
    ~Timer(){
        end = std::chrono::system_clock::now();
        duration = end - start;
        double s = duration.count();
        std::cout << "Time: " << s << "[s]\n";
    }
private:
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> duration;
};

typedef unsigned int uint;

std::subtract_with_carry_engine<unsigned int, 24, 10, 24> random_engine;
constexpr auto random_range = random_engine.max() - random_engine.min() + 1;

unsigned int get_random(unsigned int from, unsigned int to) {
  float fTmp = static_cast<float>(random_engine()) / random_range;
  return (fTmp * (to - from + 1)) + from;
}

int main() {
    std::cin.sync_with_stdio(false);
    unsigned int C, S;
    unsigned int _size;
    std::cin >> C >> S;
    Timer t;
    random_engine.seed(S);

    unsigned int N, MIN, MAX;
    for (unsigned int i = 0; i < C; i++) {
        std::cin >> N >> MIN >> MAX;
        uint* array = new uint[N+1];
        for (unsigned int j = 0; j < N; j++) {
            array[j] = get_random(MIN,MAX);
        }
        array[N] = 0;
        unsigned int max_size = N*MIN;
        unsigned int max_rep;
        unsigned int rep;
        for (unsigned int height = MIN; height < MAX; height++) {
            rep = 0;
            max_rep = 0;
            for (unsigned int x = 0; x <= N; x++) {
                rep++;
                if (height < array[x]) continue;
                if (rep > max_rep) max_rep = rep;
                rep = 0;
            }
            _size = (height+1)*(max_rep-1);
            if (_size > max_size) max_size = _size;
            if (_size < max_size / 5) break;
        }
        std::cout << max_size << std::endl;
        //printf("%u\n",max_size);
        delete[] array;
    }
}
