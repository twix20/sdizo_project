#include "stdafx.h"
#include "TwoOptTravellingSalesman.h"
#include "TravellingSalesman.h"


TwoOptTravellingSalesman::TwoOptTravellingSalesman()
{
	tour = std::make_shared<MyTable<int>>();
	new_tour = std::make_shared<MyTable<int>>();
}


TwoOptTravellingSalesman::~TwoOptTravellingSalesman()
{
}

void TwoOptTravellingSalesman::twoOptSwap(Town town, const int& i, const int& k)
{
	int size = town.size;
	new_tour = std::make_shared<MyTable<int>>();
	for (int i = 0; i < size; i++)
		new_tour->push_back(0);

	// 1. take route[0] to route[i-1] and add them in order to new_route
	for (int c = 0; c <= i - 1; ++c)
	{
		//new_tour.SetCity(c, tour.GetCity(c));
		int end = tour->get_by_index(c);
		new_tour->insert_at(c, tour->get_by_index(c));
	}

	// 2. take route[i] to route[k] and add them in reverse order to new_route
	int dec = 0;
	for (int c = i; c <= k; ++c)
	{
		//new_tour.SetCity(c, tour.GetCity(k - dec));
		new_tour->insert_at(c, tour->get_by_index(k - dec));
		dec++;
	}

	// 3. take route[k+1] to end and add them in order to new_route
	for (int c = k + 1; c < size; ++c)
	{
		//new_tour.SetCity(c, tour.GetCity(c));
		new_tour->insert_at(c, tour->get_by_index(c));
	}
}

std::shared_ptr<MyTable<int>> TwoOptTravellingSalesman::compute(Town town)
{
	//Set random tour
	for(int i = 0; i < town.size; i++)
	{
		tour->push_back(i);
		new_tour->push_back(i);
	}

	// Get tour size
	int size = tour->get_size();
	// repeat until no improvement is made 
	int improve = 0;

	while (improve < size)
	{
		double best_distance = TravellingSalesman::calculatePathScore(town, tour);

		for (int i = 0; i < size - 1; i++)
		{
			for (int k = i + 1; k < size; k++)
			{
				twoOptSwap(town, i, k);

				double new_distance = TravellingSalesman::calculatePathScore(town, new_tour);

				if (new_distance < best_distance)
				{
					// Improvement found so reset
					improve = 0;
					size = new_tour->get_size();
					tour = std::make_shared<MyTable<int>>();
					tour = new_tour;
					best_distance = new_distance;
				}
			}
		}

		improve++;
	}

	tour->push_back(tour->get_by_index(0));
	return tour;
}

std::string TwoOptTravellingSalesman::getName()
{
	return "TwoOptTravellingSalesman";
}
