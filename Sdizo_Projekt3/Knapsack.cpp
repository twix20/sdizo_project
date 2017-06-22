#include "stdafx.h"
#include "Knapsack.h"
#include <iostream>
#include <fstream>


Knapsack::Knapsack(int N, int backpackSize)
{
	_itemsCount = N;
	_backpackSize = backpackSize;

	_itemGenerator = std::unique_ptr<ItemGenerator>();
}

Knapsack::~Knapsack()
{
}

void Knapsack::generateItems()
{
	_items = _itemGenerator->generate(_itemsCount, _backpackSize);
}

void Knapsack::setItems(std::shared_ptr<MyTable<Item>> newItems)
{
	_items = newItems;
}

std::shared_ptr<MyTable<Item>> Knapsack::insertItemsIntoBackpack(IKnapsackStrategy* strategy) const
{
	return strategy->compute(_items, _backpackSize);
}

std::shared_ptr<MyTable<Item>> Knapsack::getItems() const
{
	return _items;
}

void Knapsack::printItems(std::shared_ptr<MyTable<Item>> items)
{
	std::cout << "Size: " << calculateSize(items) 
			  << " Value: " << calculateValue(items) << std::endl;

	int n = items->get_size();
	for(int i = 0; i < n; i++)
	{
		Item item = items->get_by_index(i);
		std::cout << "[V:" << item.value << " S:" << item.weight << "] ";
		//std::cout << std::fixed << std::setprecision(3) << item.getRatio() << " ";
	}
	std::cout << std::endl;
}

int Knapsack::calculateValue(std::shared_ptr<MyTable<Item>> items)
{
	int value = 0;
	for (int i = 0; i < items->get_size(); i++)
		value += items->get_by_index(i).value;

	return value;
}

int Knapsack::calculateSize(std::shared_ptr<MyTable<Item>> items)
{
	int size = 0;
	for (int i = 0; i < items->get_size(); i++)
		size += items->get_by_index(i).weight;

	return size;
}

std::shared_ptr<MyTable<Item>> Knapsack::loadFromFile(std::string fileName)
{
	std::shared_ptr<MyTable<Item>> items(new MyTable<Item>);
	std::string line;
	std::ifstream file(fileName);

	int bpSize, N;
	int weight, value;
	
	file >> bpSize >> N;
	items->push_front(Item(bpSize, N));

	for(int i = 0; i < N; i++)
	{
		file >> weight >> value;
		items->push_back(Item(weight, value));
	}


	return items;
}
