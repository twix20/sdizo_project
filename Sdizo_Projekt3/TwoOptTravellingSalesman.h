#pragma once
#include "ITravellingSalesmanStrategy.h"

class TwoOptTravellingSalesman : public ITravellingSalesmanStrategy
{
private:
	void twoOptSwap(Town town, const int& i, const int& k);
	std::shared_ptr<MyTable<int>> tour;
	std::shared_ptr<MyTable<int>> new_tour;

public:
	TwoOptTravellingSalesman();
	~TwoOptTravellingSalesman();
	std::shared_ptr<MyTable<int>> compute(Town town) override;
	std::string getName() override;
};

