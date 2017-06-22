#pragma once
#include "IKnapsackStrategy.h"

//Greedy - zach³anny
class GreedyKnapsack : public IKnapsackStrategy
{
public:
	GreedyKnapsack();
	~GreedyKnapsack();
	std::shared_ptr<MyTable<Item>> compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize) override;
	std::string getName() override;
};

