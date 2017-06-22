#include "stdafx.h"
#include "BrutforceTravellingSalesman.h"
#include "TravellingSalesman.h"
#include "Knapsack.h"


BrutforceTravellingSalesman::BrutforceTravellingSalesman()
{
	_bestPath = std::make_shared<MyTable<int>>();
	_bestScore = INT_MAX;
}


BrutforceTravellingSalesman::~BrutforceTravellingSalesman()
{
}

std::shared_ptr<MyTable<int>> BrutforceTravellingSalesman::compute(Town town)
{
	std::shared_ptr<MyTable<int>> firstPath(new MyTable<int>);
	for(int i = 0; i < town.size; i++)
	{
		firstPath->push_back(i);
	}

	permutate(town, firstPath, 1, firstPath->get_size() - 1);

	return _bestPath;
}

std::string BrutforceTravellingSalesman::getName()
{
	return "BrutforceTravellingSalesman";
}

void BrutforceTravellingSalesman::permutate(Town town, std::shared_ptr<MyTable<int>> path, int l, int r)
{
	if (l == r)
	{
		//New permutation
		for (int i = 0; i < path->get_size(); i++)
		{
			std::shared_ptr<MyTable<int>> tempPath(new MyTable<int>);
			for (int z = 0; z < path->get_size(); z++)
			{
				tempPath->push_back(path->get_by_index(z));
			}
			tempPath->push_back(0);

			setBestIfBetter(town, tempPath);
		}

	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			path->swap(l, i);
			permutate(town, path, l + 1, r);
			path->swap(l, i); //backtrack
		}
	}
}

void BrutforceTravellingSalesman::setBestIfBetter(Town town, std::shared_ptr<MyTable<int>> newPath)
{
	int newPathScore = TravellingSalesman::calculatePathScore(town, newPath);

	if (newPathScore < _bestScore)
	{
		_bestScore = newPathScore;
		_bestPath = std::make_shared<MyTable<int>>();

		for (int i = 0; i < newPath->get_size(); i++)
		{
			_bestPath->push_back(newPath->get_by_index(i));
		}
	}
}
