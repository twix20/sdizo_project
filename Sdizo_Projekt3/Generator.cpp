#include "stdafx.h"
#include "Generator.h"
#include <stdlib.h> 


Generator::Generator()
{
}


Generator::~Generator()
{
}

int Generator::generateNumber(int min, int max)
{

	return min + rand() % (max - min);
}
