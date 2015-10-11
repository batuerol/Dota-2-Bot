#pragma once
#include <chrono>

class StopWatch
{

public:
	StopWatch();
	void reset();
	template<typename T = float> T getElapsedTime() const;

private:	
	std::chrono::high_resolution_clock::time_point start;
};