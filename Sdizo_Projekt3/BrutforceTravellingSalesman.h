#pragma once
#include "ITravellingSalesmanStrategy.h"
#include <memory>

class BrutforceTravellingSalesman : public ITravellingSalesmanStrategy
{
private:
	int _bestScore;
	std::shared_ptr<MyTable<int>> _bestPath;

	void setBestIfBetter(Town town, std::shared_ptr<MyTable<int>> newPath);
	void permutate(Town town, std::shared_ptr<MyTable<int>> path, int l, int r);

public:
	BrutforceTravellingSalesman();
	~BrutforceTravellingSalesman();
	std::shared_ptr<MyTable<int>> compute(Town town) override;
	std::string getName() override;
};

