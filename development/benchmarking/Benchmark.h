#ifndef _BENCHMARK_H_
#define _BENCHMARK_H_

#include "Vec.h"
#include "VecStruct.h"
#include "VecClass.h"
#include "VecClassPointers.h"

class Benchmark {
public:
	void profileTick();
	void profileTock(const std::string& label);
	void writePairsToCSV(const std::string& filename);
private:
	std::vector<std::pair<std::string, double>> m_results;
	std::chrono::steady_clock::time_point m_start;
	std::chrono::steady_clock::time_point m_stop;
};

#endif