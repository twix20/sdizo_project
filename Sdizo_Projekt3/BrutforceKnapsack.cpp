#include "stdafx.h"
#include "BrutforceKnapsack.h"
#include "Knapsack.h"


BrutforceKnapsack::BrutforceKnapsack()
{
	_itemsInBackpack = std::make_shared<MyTable<Item>>();
}


BrutforceKnapsack::~BrutforceKnapsack()
{
}

std::shared_ptr<MyTable<Item>> BrutforceKnapsack::compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize)
{
	//auto comp = [](Item& a, Item&b) { return a.value > b.value; };
	//auto compEq = [](Item& a, Item&b) { return a.value == b.value; };
	//allItems->sort(comp, 0, allItems->get_size() - 1);

	permutate(allItems, 0, allItems->get_size() - 1, backpackSize);

	return _itemsInBackpack;
}

std::string BrutforceKnapsack::getName()
{
	return "BrutforceKnapsack";
}


void BrutforceKnapsack::permutate(std::shared_ptr<MyTable<Item>> items, int l, int r, int backpackSize)
{
	if (l == r)
	{
		//Knapsack::printItems(items);
		//system("pause");

		//Nowa permutacja
		for(int i = 0; i < items->get_size(); i++)
		{
			std::shared_ptr<MyTable<Item>> tempItems(new MyTable<Item>);
			for(int z = 0; z < items->get_size() - i; z++)
			{
				tempItems->push_back(items->get_by_index(z));
			}

			setBestIfBetter(tempItems, backpackSize);
		}

	}
	else
	{
		for (int i = l; i <= r; i++)
		{
			items->swap(l, i);
			permutate(items, l + 1, r, backpackSize);
			items->swap(l, i); //backtrack
		}
	}
}

void BrutforceKnapsack::setBestIfBetter(std::shared_ptr<MyTable<Item>> items, int backpackSize)
{
	int itemsValue = Knapsack::calculateValue(items);
	int itemsSize = Knapsack::calculateSize(items);
	if (itemsSize <= backpackSize && itemsValue > bestValue)
	{
		bestValue = itemsValue;
		bestWeight = itemsSize;

		_itemsInBackpack = std::make_shared<MyTable<Item>>();
		for (int i = 0; i < items->get_size(); i++)
		{
			_itemsInBackpack->push_back(items->get_by_index(i));
		}
	}
}