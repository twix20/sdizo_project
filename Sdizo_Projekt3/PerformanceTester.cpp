#include "stdafx.h"
#include "PerformanceTester.h"
#include <memory>
#include "Knapsack.h"
#include "BrutforceKnapsack.h"
#include "GreedyKnapsack.h"
#include "DynamicKnapsack.h"
#include <string>
#include <iostream>
#include "ITravellingSalesmanStrategy.h"
#include "TravellingSalesman.h"
#include "GreedyTravellingSalesman.h"
#include "BrutforceTravellingSalesman.h"
#include "TwoOptTravellingSalesman.h"


PerformanceTester::PerformanceTester(): elapsedTime(0)
{
}

PerformanceTester::~PerformanceTester()
{
}

void PerformanceTester::performTestKnapsack(int N, int backpackSize, IKnapsackStrategy* strategy)
{
	std::unique_ptr<Knapsack> knapsack(new Knapsack(N, backpackSize));

	int avgTime = 0;
	for (int t = 0; t < testTimes; t++)
	{
		knapsack->generateItems();

		startTimer();
		knapsack->insertItemsIntoBackpack(strategy);
		stopTimer();

		avgTime = (avgTime + elapsedTime) / 2;
	}

	std::cout << "Strategy: " << strategy->getName() 
		<< " Elements: " << N
		<< " BackpackSize: " << backpackSize
		<< " AvgTime: " << avgTime
		<< std::endl;
}


void PerformanceTester::testKnapsack()
{
	std::cout << "testKnapsack\n";

	int brutforceBackpackSize[3] = { 10, 20, 30 };
	int brutforceElementsCount[5] = { 5, 6, 7, 8, 9 };
	for(int i = 0; i < 5; i++)
		for(int j = 0; j < 3; j++)
			performTestKnapsack(brutforceElementsCount[i], brutforceBackpackSize[j], new BrutforceKnapsack());


	int backpackSize[3]{ 300, 400,  500 };
	int elementsCount[5] = { 50, 100, 150, 200, 250 };
	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			performTestKnapsack(elementsCount[i], backpackSize[j], new DynamicKnapsack());

	for (int i = 0; i < 5; i++)
		for (int j = 0; j < 3; j++)
			performTestKnapsack(elementsCount[i], backpackSize[j], new GreedyKnapsack());

}

void PerformanceTester::performTestSalesman(int townSize, ITravellingSalesmanStrategy* strategy)
{
	std::unique_ptr<TravellingSalesman> salesman(new TravellingSalesman());

	int avgTime = 0;
	for (int t = 0; t < testTimes; t++)
	{
		salesman->generateTown(townSize);

		startTimer();
		salesman->calculatePath(strategy);
		stopTimer();

		avgTime = (avgTime + elapsedTime) / 2;
	}

	std::cout << "Strategy: " << strategy->getName()
		<< " TownSize: " << townSize
		<< " AvgTime: " << avgTime
		<< std::endl;
}

void PerformanceTester::testSalesman()
{
	std::cout << "testSalesman\n";

	int brutforceTownSizes[3] = { 5, 10, 11 };
	for (int i = 0; i < 1; i++)
		performTestSalesman(brutforceTownSizes[i], new BrutforceTravellingSalesman);

	int townSizes[3] = { 50, 100, 200 };
	for (int i = 0; i < 3; i++)
		performTestSalesman(townSizes[i], new GreedyTravellingSalesman);

	for (int i = 0; i < 3; i++)
		performTestSalesman(townSizes[i], new TwoOptTravellingSalesman);
}


void PerformanceTester::startTimer()
{
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&startTime);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);

}

void PerformanceTester::stopTimer()
{
	LARGE_INTEGER stop;
	DWORD_PTR oldmask = SetThreadAffinityMask(GetCurrentThread(), 0);
	QueryPerformanceCounter(&stop);
	SetThreadAffinityMask(GetCurrentThread(), oldmask);

	elapsedTime = static_cast<double>(stop.QuadPart - startTime.QuadPart);
}

