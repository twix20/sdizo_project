#pragma once
#include "IKnapsackStrategy.h"

//
class DynamicKnapsack: public IKnapsackStrategy
{
public:
	DynamicKnapsack();
	~DynamicKnapsack();
	std::shared_ptr<MyTable<Item>> compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize) override;
	std::string getName() override;
};

