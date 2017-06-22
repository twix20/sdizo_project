#pragma once
#include "ITravellingSalesmanStrategy.h"

struct tempPath
{
	int from;
	int to;
	int cost;

	tempPath()
	{
		
	}

	tempPath(int from, int to, int cost)
	{
		this->from = from;
		this->to = to;
		this->cost = cost;
	}
};

class GreedyTravellingSalesman : public ITravellingSalesmanStrategy
{

private:
	std::unique_ptr<bool[]> _visited;
	tempPath selectNextMinCostPath(std::shared_ptr<MyTable<tempPath>> allPaths, int from) const;

public:
	GreedyTravellingSalesman();
	~GreedyTravellingSalesman();
	std::shared_ptr<MyTable<int>> compute(Town town) override;
	std::string getName() override;
};

