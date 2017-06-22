#pragma once
#include <memory>
#include "ItemGenerator.h"
#include "IKnapsackStrategy.h"

class Knapsack
{
private:
	std::unique_ptr<ItemGenerator> _itemGenerator;
	std::shared_ptr<MyTable<Item>> _items;

	int _itemsCount;
	int _backpackSize;

public:
	Knapsack(int N, int backpackSize);
	~Knapsack();

	void generateItems();
	void setItems(std::shared_ptr<MyTable<Item>> newItems);

	std::shared_ptr<MyTable<Item>> insertItemsIntoBackpack(IKnapsackStrategy* strategy) const;

	std::shared_ptr<MyTable<Item>> getItems() const;
	static void printItems(std::shared_ptr<MyTable<Item>> items);

	static int calculateValue(std::shared_ptr<MyTable<Item>> items);
	static int calculateSize(std::shared_ptr<MyTable<Item>> items);
	static std::shared_ptr<MyTable<Item>> loadFromFile(std::string fileName);
		
};

