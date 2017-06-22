#include "stdafx.h"
#include "GreedyTravellingSalesman.h"
#include "TravellingSalesman.h"


GreedyTravellingSalesman::GreedyTravellingSalesman()
{
}


GreedyTravellingSalesman::~GreedyTravellingSalesman()
{
}

std::shared_ptr<MyTable<int>> GreedyTravellingSalesman::compute(Town town)
{
	std::shared_ptr<MyTable<int>> returnPath(new MyTable<int>);
	std::shared_ptr<MyTable<tempPath>> allPaths(new MyTable<tempPath>);
	for(int i = 0; i < town.size; i++)
	{
		for(int j = 0; j < town.size; j++)
		{
			auto x = tempPath(i, j, town.cities[i][j]);
			if (x.cost == 0)
				continue;

			allPaths->push_back(x);
		}
	}

	auto cmp = [](tempPath& a, tempPath& b) { return a.cost > b.cost; };
	allPaths->sort(cmp, 0, allPaths->get_size() - 1);

	_visited = std::make_unique<bool[]>(allPaths->get_size());
	for (int i = 0; i < allPaths->get_size(); i++)
		_visited[i] = false;

	int currentlyVisitedCount = 1;
	int currentlyVisited = 0;
	returnPath->push_back(currentlyVisited);
	_visited[currentlyVisited] = true;

	while(currentlyVisitedCount <= town.size)
	{
		tempPath minValidPath = selectNextMinCostPath(allPaths, currentlyVisited);
		if(minValidPath.from == -1)
		{
			break;
		}
		else
		{
			_visited[minValidPath.to] = true;
			currentlyVisitedCount++;
			currentlyVisited = minValidPath.to;
			returnPath->push_back(minValidPath.to);
		}
	}

	returnPath->push_back(0);
	return returnPath;
}

std::string GreedyTravellingSalesman::getName()
{
	return "GreedyTravellingSalesman";
}

tempPath GreedyTravellingSalesman::selectNextMinCostPath(std::shared_ptr<MyTable<tempPath>> allPaths, int from) const
{
	for(int i = 0; i < allPaths->get_size(); i++)
	{
		tempPath cp = allPaths->get_by_index(i);
		if(cp.from == from && !_visited[cp.to])
		{
			allPaths->remove_by_index(i);
			return cp;
		}
	}
	return tempPath(-1, -1, -1);
}
