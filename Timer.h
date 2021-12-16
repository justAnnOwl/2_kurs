#pragma once

#include <chrono> // дл€ функций из std::chrono
using namespace std;
class Timer
{
private:
	// ѕсевдонимы типов используютс€ дл€ удобного доступа к вложенным типам
	using clock_t = chrono::high_resolution_clock;
	using second_t = chrono::duration<double, ratio<1> >;

	chrono::time_point<clock_t> timer;

public:
	Timer() : timer(clock_t::now())
	{
	}

	void Reset()
	{
		timer = clock_t::now();
	}

	double Elapsed() const
	{
		return chrono::duration_cast<second_t>(clock_t::now() - timer).count();
	}
};
//#include <stdio.h>
//#include <time.h>
//
//volatile unsigned sink;
//int main(void)
//{
//	clock_t start = clock();
//
//	for (size_t i = 0; i < 10000000; ++i)
//		sink++;
//
//	clock_t end = clock();
//	double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
//
//	printf("for loop took %f seconds to execute \n", cpu_time_used);
//}