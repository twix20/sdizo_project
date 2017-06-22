#include "stdafx.h"
#include "DynamicKnapsack.h"
#include <algorithm>
#include "Knapsack.h"


DynamicKnapsack::DynamicKnapsack()
{
}


DynamicKnapsack::~DynamicKnapsack()
{
}

std::shared_ptr<MyTable<Item>> DynamicKnapsack::compute(std::shared_ptr<MyTable<Item>> allItems, int backpackSize)
{
	int n = allItems->get_size();
	std::unique_ptr<std::unique_ptr<int[]>[]> A = std::make_unique<std::unique_ptr<int[]>[]>(n + 1);
	for (int i = 0; i < n + 1; ++i)
		A[i] = std::make_unique<int[]>(backpackSize + 1);

	for (int i = 0; i < n + 1; i++)
	{
		for(int w = 0; w < backpackSize + 1; w++)
		{
			if(i == 0 || w == 0)
			{
				A[i][w] = 0;
				continue;
			}

			Item item = allItems->get_by_index(i - 1);
			A[i][w] = item.weight > w ? A[i - 1][w] : 
										std::max(A[i - 1][w], A[i - 1][w - item.weight] + item.value);
		}
	}

	int i = n;
	int w = backpackSize;
	std::shared_ptr<MyTable<Item>> itemsInBackpack(new MyTable<Item>);

	while(i > 0 && w > 0)
	{
		if(A[i][w] != A[i- 1][w])
		{
			Item item = allItems->get_by_index(i - 1);
			itemsInBackpack->push_back(item);

			w -= item.weight;
		}
		i--;
	}

	return itemsInBackpack;
}

std::string DynamicKnapsack::getName()
{
	return "DynamicKnapsack";
}
