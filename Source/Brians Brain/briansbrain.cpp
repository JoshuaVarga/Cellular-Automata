#include "briansbrain.h"

std::string BriansBrain::getName()
{
	return name;
}

void BriansBrain::init()
{
	int percent;
	srandom();

	for (int i = 0; i < cellCount; i++)
	{
		percent = random(1, 100);

		if (percent > 95)
		{
			population.push_back(on);
		}

		else if (percent > 90)
		{
			population.push_back(dying);
		}

		else
		{
			population.push_back(off);
		}
	}
}

void BriansBrain::update()
{
	std::vector<cell> new_population(cellCount);
	int neighbours;

	for (int i = 0; i < cellCount; i++)
	{
		switch (population[i])
		{
		case off:
			neighbours = countNeighbours(i);

			switch (neighbours)
			{
			case 2:
				new_population[i] = on;
				break;
			default:
				new_population[i] = off;
				break;
			}

			break;

		case on:
			new_population[i] = dying;
			break;

		default:
			new_population[i] = off;
			break;
		}
	}

	population = new_population;
}

int BriansBrain::countNeighbours(int index)
{
	int neighbours = 0;

	int x = getX(index);
	int y = getY(index);

	int north = (gridSize * ((y - 1 + gridSize) % gridSize)) + x;
	int north_east = (gridSize * ((y - 1 + gridSize) % gridSize)) + ((x + 1 + gridSize) % gridSize);
	int east = (gridSize * y) + ((x + 1 + gridSize) % gridSize);
	int south_east = (gridSize * ((y + 1 + gridSize) % gridSize)) + ((x + 1 + gridSize) % gridSize);
	int south = (gridSize * ((y + 1 + gridSize) % gridSize)) + x;
	int south_west = (gridSize * ((y + 1 + gridSize) % gridSize)) + ((x - 1 + gridSize) % gridSize);
	int west = (gridSize * y) + ((x - 1 + gridSize) % gridSize);
	int north_west = (gridSize * ((y - 1 + gridSize) % gridSize)) + ((x - 1 + gridSize) % gridSize);

	if (population[north] == on)      neighbours++;
	if (population[north_east] == on) neighbours++;
	if (population[east] == on)       neighbours++;
	if (population[south_east] == on) neighbours++;
	if (population[south] == on)      neighbours++;
	if (population[south_west] == on) neighbours++;
	if (population[west] == on)       neighbours++;
	if (population[north_west] == on) neighbours++;

	return neighbours;
}

sf::Color BriansBrain::paint(int index)
{
	sf::Color colour;

	if (population[index] == on)
	{
		colour = sf::Color::Blue;
	}

	else if (population[index] == dying)
	{
		colour = sf::Color::White;
	}

	else
	{
		colour = sf::Color::Black;
	}

	return colour;
}


