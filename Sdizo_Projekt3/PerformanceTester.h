#pragma once
#include <windows.h>

class ITravellingSalesmanStrategy;
class IKnapsackStrategy;

class PerformanceTester
{
public:
	PerformanceTester();
	~PerformanceTester();

	void testKnapsack();
	void testSalesman();

private:
	LARGE_INTEGER startTime;
	double elapsedTime;

	const int testTimes = 100;

	void startTimer();
	void stopTimer();

	void performTestKnapsack(int N, int backpackSize, IKnapsackStrategy* strategy);
	void performTestSalesman(int townSize, ITravellingSalesmanStrategy* strategy);
};

