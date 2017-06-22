#pragma once
#include <memory>
#include "Knapsack.h"
#include "TravellingSalesman.h"

class Menu
{
private:
	const std::string itemsFile = "items.txt";
	const std::string townFile = "town.txt";

	std::unique_ptr<Knapsack> _knapsack;
	std::unique_ptr<TravellingSalesman> _travellingSalesman;

public:
	Menu();
	~Menu();

	static void displayMainMenu();
	static void displayLoadData();
	static void displayKnapsack();
	static void displayTravellingSalesman();

	void mainMenu();
	void loadData();
	void knapsack() const;
	void travellingSalesman() const;
};

