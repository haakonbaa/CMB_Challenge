#pragma once

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