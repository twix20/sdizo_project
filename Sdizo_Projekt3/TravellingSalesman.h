#pragma once
#include "TownGenerator.h"
#include "MyTable.h"

class ITravellingSalesmanStrategy;

struct Town
{
	int** cities;
	int size;

	Town()
	{
	}

	Town(int** cit, int s)
	{
		cities = cit;
		size = s;
	}
};

class TravellingSalesman
{
private:
	std::unique_ptr<TownGenerator> _townGenerator;
	Town _town;

public:
	TravellingSalesman();
	~TravellingSalesman();

	void generateTown(int size);
	void deleteTown();
	void setTown(Town newTown);
	void printTown() const;
	void printPath(std::shared_ptr<MyTable<int>> path) const;
	static void printPath(Town town, std::shared_ptr<MyTable<int>> path);

	std::shared_ptr<MyTable<int>> calculatePath(ITravellingSalesmanStrategy* strategy) const;

	static int calculatePathScore(Town town, std::shared_ptr<MyTable<int>> path);
	static Town loadFromFile(std::string fileName);
};

