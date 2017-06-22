#pragma once
#include "MyTable.h"
#include <memory>

struct Town;

class ITravellingSalesmanStrategy
{
public:
	ITravellingSalesmanStrategy();
	virtual ~ITravellingSalesmanStrategy();

	virtual std::shared_ptr<MyTable<int>> compute(Town town) = 0;
	virtual std::string getName() = 0;
};

