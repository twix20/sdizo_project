#include "stdafx.h"
#include "ItemGenerator.h"
#include <memory>
#include <iostream>


ItemGenerator::ItemGenerator()
{
}


ItemGenerator::~ItemGenerator()
{
}

std::unique_ptr<MyTable<Item>> ItemGenerator::generate(int N, int backpackSize)
{
	std::unique_ptr<MyTable<Item>> items(new MyTable<Item>);

	int totalItemSize = 0;

	int max = backpackSize / N;
	int min = backpackSize / (N + backpackSize* 0.5);
	for(int i = 0; i < N; i++)
	{
		int size = Generator::generateNumber(min, max);
		int value = Generator::generateNumber(minValue, maxValue);
		totalItemSize += size;

		items->push_back(Item(size, value));
	}

	return items;
}
