#pragma once
#include <memory>

class TownGenerator
{
private:
	int _minPathDistance = 1;
	int _mxPathDistance = 9;
public:
	TownGenerator();
	~TownGenerator();

	int** generateTown(int n) const;
};

