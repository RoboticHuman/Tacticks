#include "Timer.h"
using namespace std::chrono;

Timer::Timer() : timePrev(high_resolution_clock::now())
{

}
double Timer::GetDelta()
{
	auto timeCurrent = high_resolution_clock::now();
	duration< double > delta( timeCurrent - timePrev );
	timePrev = high_resolution_clock::now();
	return delta.count();
}
