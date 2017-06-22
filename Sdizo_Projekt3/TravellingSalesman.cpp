#include "stdafx.h"
#include "TravellingSalesman.h"
#include "ITravellingSalesmanStrategy.h"
#include <iostream>
#include <fstream>


TravellingSalesman::TravellingSalesman()
{
	_townGenerator = std::make_unique<TownGenerator>();
	_town = Town(nullptr, 0);
}


TravellingSalesman::~TravellingSalesman()
{
}

void TravellingSalesman::generateTown(int n)
{
	auto x = _townGenerator->generateTown(n);
	_town = Town(x, n);
}

void TravellingSalesman::deleteTown()
{
	for (int i = 0; i < _town.size; i++)
		delete[] _town.cities[i];

	delete[] _town.cities;

	setTown(Town(nullptr, 0));
}

void TravellingSalesman::setTown(Town newTown)
{
	_town = newTown;
}

void TravellingSalesman::printTown() const
{
	int n = _town.size;
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j <n; j++)
		{
			std::cout << _town.cities[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void TravellingSalesman::printPath(Town town, std::shared_ptr<MyTable<int>> path)
{
	//Print path
	int pathScore = calculatePathScore(town, path);

	std::cout << "Path score: " << pathScore << std::endl;
	for (int z = 0; z < path->get_size(); z++)
	{
		std::cout << path->get_by_index(z) << " ";
	}
	std::cout << std::endl;
}

void TravellingSalesman::printPath(std::shared_ptr<MyTable<int>> path) const
{
	printPath(_town, path);
}



std::shared_ptr<MyTable<int>> TravellingSalesman::calculatePath(ITravellingSalesmanStrategy* strategy) const
{
	return strategy->compute(_town);
}

int TravellingSalesman::calculatePathScore(Town town, std::shared_ptr<MyTable<int>> path)
{
	int v = 0;
	int s = path->get_size() - 1;
	for(int i = 0; i < s; i++)
	{
		//for (int k = 0; k < path->get_size(); k++)
		//	std::cout << path->get_by_index(k) << " ";
		//std::cout << std::endl;

		int x = path->get_by_index(i);
		int y = path->get_by_index(i + 1);
		v += town.cities[x][y];
	}
	return v;
}

Town TravellingSalesman::loadFromFile(std::string fileName)
{
	int  N;
	Town town;

	std::string line;
	std::ifstream file(fileName);

	file >> N;

	int** cities = new int*[N];
	for (int i = 0; i < N; ++i)
		cities[i] = new int[N];

	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			file >> cities[i][j];
		}
	}

	town.cities = cities;
	town.size = N;

	return town;
}
