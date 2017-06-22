#pragma once
#include "IKnapsackStrategy.h"

//Brutforce - Przeglad zupelny
class BrutforceKnapsack : public IKnapsackStrategy
{

private:
	std::shared_ptr<MyTable<Item>> _itemsInBackpack;
	int bestValue = 0;
	int bestWeight = 0;

	void setBestIfBetter(std::shared_ptr<MyTable<Item>> items, int backpackSize);

	void permutate(std::shared_ptr<MyTable<Item>> items, int l, int r, int backpackSize);
public:
	BrutforceKnapsack();
	~BrutforceKnapsack();


	std::shared_ptr<MyTable<Item>> compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize) override;
	std::string getName() override;
};

