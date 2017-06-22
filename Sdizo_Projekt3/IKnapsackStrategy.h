#pragma once
#include <memory>
#include "MyTable.h"
#include "ItemGenerator.h"

class IKnapsackStrategy
{
public:
	IKnapsackStrategy();
	virtual ~IKnapsackStrategy();

	virtual std::string getName() = 0;
	virtual std::shared_ptr<MyTable<Item>> compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize) = 0;
};

