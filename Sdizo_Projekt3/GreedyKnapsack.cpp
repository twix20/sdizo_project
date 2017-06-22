#include "stdafx.h"
#include "GreedyKnapsack.h"
#include "Knapsack.h"


GreedyKnapsack::GreedyKnapsack()
{
}


GreedyKnapsack::~GreedyKnapsack()
{
}

std::shared_ptr<MyTable<Item>> GreedyKnapsack::compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize)
{
	std::shared_ptr<MyTable<Item>> itemsInBackpack(new MyTable<Item>);

	int n = allItems->get_size();

	//sort DESC
	auto cmp = [](Item& a, Item& b) {return a.getRatio() < b.getRatio(); };
	allItems->sort(cmp, 0, n - 1);


	int curWeight = 0;  
	for (int i = 0; i < n; i++)
	{
		Item item = allItems->get_by_index(i);
		if (curWeight + item.weight <= backpackSize)
		{
			curWeight += item.weight;
			itemsInBackpack->push_back(item);
		}
		else
		{
			break;
		}
	}

	return itemsInBackpack;
}

std::string GreedyKnapsack::getName()
{
	return "GreedyKnapsack";
}
