#include "stdafx.h"
#include "Menu.h"
#include "BrutforceKnapsack.h"
#include "GreedyKnapsack.h"
#include "DynamicKnapsack.h"
#include "BrutforceTravellingSalesman.h"
#include "GreedyTravellingSalesman.h"
#include "TwoOptTravellingSalesman.h"


Menu::Menu()
{
}


Menu::~Menu()
{
}

int GetInput()
{
	int choice;
	std::cin >> choice;
	return choice;
}


void Menu::displayMainMenu()
{
	std::cout << "Main Menu\n";
	std::cout << "1 - Wczytaj dane\n";
	std::cout << "2 - Problem Plecakowy\n";
	std::cout << "3 - Problem Komiwojazera\n";
	std::cout << "4 - Quit\n";
	std::cout << "Selection: ";
}

void Menu::displayLoadData()
{
	std::cout << "Wczytaj dane\n";
	std::cout << "1 - Przedmioty z pliku\n";
	std::cout << "2 - Wygeneruj losowo przedmioty\n";
	std::cout << "3 - Miasto z pliku\n";
	std::cout << "4 - Wygeneruj losowo miasto\n";
	std::cout << "5 - Powrot\n";
	std::cout << "Selection: ";
}

void Menu::displayKnapsack()
{
	std::cout << "Problem plecakowy\n";
	std::cout << "1 - Zupelny\n";
	std::cout << "2 - Zachlanny\n";
	std::cout << "3 - Dynamiczny\n";
	std::cout << "4 - Powrot\n";
	std::cout << "Selection: ";
}

void Menu::displayTravellingSalesman()
{
	std::cout << "Problem Komiwojazera\n";
	std::cout << "1 - Zupelny\n";
	std::cout << "2 - Zachlanny\n";
	std::cout << "3 - 2opt\n";
	std::cout << "4 - Powrot\n";
	std::cout << "Selection: ";
}

void Menu::mainMenu()
{
	int choice = 0;
	do
	{
		system("cls");
		displayMainMenu();
		choice = GetInput();
		switch (choice)
		{
		case 1:
			loadData();
			break;
		case 2:
			knapsack();
			break;
		case 3:
			travellingSalesman();
			break;
		default:
			break;
		}
	} while (choice != 4);
}

void Menu::loadData()
{
	std::shared_ptr<MyTable<Item>> items;
	Town t;
	Item first;
	int choice = 0;
	int n, bpSize;
	do
	{
		system("cls");
		displayLoadData();
		choice = GetInput();
		switch (choice)
		{
		case 1:
			items = Knapsack::loadFromFile(this->itemsFile);
			first = items->get_by_index(0); // First item contains bpSize and N
			items->remove_by_index(0);

			_knapsack = std::make_unique<Knapsack>(first.value, first.weight);
			_knapsack->setItems(items);

			std::cout << "Pomyslnie wczytano dane\n";
			system("pause");
			break;
		case 2:
			std::cout << "Podaj ilosc przedmiotow i pojemnosc plecaka\n";
			n = GetInput();
			bpSize = GetInput();

			_knapsack = std::make_unique<Knapsack>(n, bpSize);
			_knapsack->generateItems();

			std::cout << "Pomyslnie wygenerowano dane\n";
			system("pause");
			break;
		case 3:
			t = TravellingSalesman::loadFromFile(this->townFile);
			_travellingSalesman = std::make_unique<TravellingSalesman>();
			_travellingSalesman->setTown(t);

			std::cout << "Pomyslnie wczytano dane\n";
			system("pause");
			break;
		case 4:
			std::cout << "Podaj wielkosc miasta\n";
			n = GetInput();

			_travellingSalesman = std::make_unique<TravellingSalesman>();
			_travellingSalesman->generateTown(n);

			std::cout << "Pomyslnie wygenerowano dane\n";
			system("pause");
		default:
			break;
		}
	} while (choice != 5);
}

void Menu::knapsack() const
{
	int choice = 0;
	std::shared_ptr<MyTable<Item>> r;
	do
	{
		system("cls");
		displayKnapsack();
		choice = GetInput();
		switch (choice)
		{
		case 1:
			r = _knapsack->insertItemsIntoBackpack(new BrutforceKnapsack);
			Knapsack::printItems(r);

			system("pause");
			break;
		case 2:
			r = _knapsack->insertItemsIntoBackpack(new GreedyKnapsack);
			Knapsack::printItems(r);

			system("pause");
			break;
		case 3:
			r = _knapsack->insertItemsIntoBackpack(new DynamicKnapsack);
			Knapsack::printItems(r);

			system("pause");
			break;
		default:
			break;
		}
	} while (choice != 4);
}

void Menu::travellingSalesman() const
{
	int choice = 0;
	std::shared_ptr<MyTable<int>> r;
	do
	{
		system("cls");
		displayTravellingSalesman();
		choice = GetInput();
		switch (choice)
		{
		case 1:
			r = _travellingSalesman->calculatePath(new BrutforceTravellingSalesman);
			_travellingSalesman->printPath(r);

			system("pause");
			break;
		case 2:
			r = _travellingSalesman->calculatePath(new GreedyTravellingSalesman);
			_travellingSalesman->printPath(r);

			system("pause");
			break;
		case 3:
			r = _travellingSalesman->calculatePath(new TwoOptTravellingSalesman);
			_travellingSalesman->printPath(r);

			system("pause");
			break;
		default:
			break;
		}
	} while (choice != 4);
}
