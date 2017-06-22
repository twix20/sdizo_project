#pragma once
#include <memory>
#include "MyTable.h"
#include "Generator.h"

struct Item
{
	int weight;
	int value;

	Item()
	{
	}

	Item(int s, int v)
	{
		weight = s;
		value = v;
	}

	float getRatio() const
	{
		if (value != 0)
			return static_cast<float>(value) / static_cast<float>(weight);
		return 0;
	}
};

class ItemGenerator
{
public:
	static const int minValue = 7;
	static const int maxValue = 31;

	ItemGenerator();
	~ItemGenerator();

	static std::unique_ptr<MyTable<Item>> generate(int N, int backpackSize);
};

