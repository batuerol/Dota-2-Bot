#include "StopWatch.h"

StopWatch::StopWatch()
{
	start = std::chrono::high_resolution_clock::now();
}

void StopWatch::reset()
{	
	start = std::chrono::high_resolution_clock::now();
}

template<typename T>
T StopWatch::getElapsedTime() const
{
	using std::chrono::duration;

	return std::chrono::duration_cast<duration<T>>(start - std::chrono::high_resolution_clock::now()).count();
}