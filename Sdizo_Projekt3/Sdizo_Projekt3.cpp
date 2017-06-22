// Sdizo_Projekt3.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include "Knapsack.h"
#include "BrutforceKnapsack.h"
#include "GreedyKnapsack.h"
#include "DynamicKnapsack.h"
#include "TownGenerator.h"
#include "TravellingSalesman.h"
#include "BrutforceTravellingSalesman.h"
#include "GreedyTravellingSalesman.h"
#include "PerformanceTester.h"
#include "TwoOptTravellingSalesman.h"
#include "Menu.h"


int main()
{
	srand(time(nullptr));

	std::unique_ptr<Menu> menu(new Menu);
	menu->mainMenu();

	//PerformanceTester* p = new PerformanceTester();
	//p->testKnapsack();
	//p->testSalesman();

	system("pause");
    return 0;
}

