#include "stdafx.h"
#include "TownGenerator.h"
#include "Generator.h"


TownGenerator::TownGenerator()
{
}


TownGenerator::~TownGenerator()
{
}


int** TownGenerator::generateTown(int n) const
{
	int** town = new int*[n];
	for (int i = 0; i < n; ++i)
	{
		town[i] = new int[n];
		for(int k = 0; k < n; k++)
		{
			int val = k == i ? 0 : Generator::generateNumber(_minPathDistance, _mxPathDistance);
			town[i][k] = val;
		}
	}

	return town;
}
