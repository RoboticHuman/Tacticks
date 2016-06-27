#pragma once
#include <chrono>

class Timer
{
private:
	std::chrono::time_point< std::chrono::high_resolution_clock > timePrev;
public:
    Timer();
    double GetDelta();
};
