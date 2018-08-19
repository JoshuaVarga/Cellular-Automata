/**
briansbrain.cpp
Purpose: Implement Brian's Brain cellular automaton.

@author Joshua Varga
@version 1.0
*/

#include "briansbrain.h"

// Sets the name of the cellular automaton.
void BriansBrain::setName(std::string rules)
{
	name = rules;
}

// Gets the name of the cellular automaton.
std::string BriansBrain::getName()
{
	return name;
}

// Generates random states states for the first generation of cells.
void BriansBrain::init()
{
	int percent;
	srandom();

	// Loop through cells and set them to on or off randomly.
	for (int i = 0; i < cellCount; i++)
	{
		percent = random(1, 100);

		if (percent > 75)
		{
			population.push_back(on);
		}

		else if (percent > 50)
		{
			population.push_back(dying);
		}

		else
		{
			population.push_back(off);
		}
	}
}

// Replaces the current population with the next generation of cells.
void BriansBrain::update()
{
	// Next generation.
	std::vector<cell> new_population(cellCount);

	int neighbours;

	// Loop through all cells and change their state in the next generation based on neighbours.
	for (int i = 0; i < cellCount; i++)
	{
		switch (population[i])
		{
			case on:
			{
				new_population[i] = dying;
				break;
			}

			case dying:
			{
				new_population[i] = off;
				break;
			}

			default:
			{
				neighbours = countNeighbours(i);

				switch (neighbours)
				{
					case 2:
					{
						new_population[i] = on;
						break;
					}

					default:
					{
						new_population[i] = off;
						break;
					}
				}
			}
		}
	}

	population = new_population;
}

// Cycles the state of a cell at specific coordinates.
void BriansBrain::cycleCell(int x, int y)
{
	int index = getIndex(x, y);

	switch (population[index])
	{
	case on:
	{
		population[index] = dying;
		break;
	}

	case dying:
	{
		population[index] = off;
		break;
	}

	default:
	{
		population[index] = on;
		break;
	}
	}
}

// Counts the neighbours in the Moore neighbourhood. 
int BriansBrain::countNeighbours(int index)
{
	int neighbours = 0;

	int x = getX(index);
	int y = getY(index);

	// NW | N | NE
	// -----------
	//  W | i | E
	// -----------
	// SW | S | SE

	int north = (gridSize * ((y - 1 + gridSize) % gridSize)) + x;

	int north_east = (gridSize * ((y - 1 + gridSize) % gridSize)) +
		((x + 1 + gridSize) % gridSize);

	int east = (gridSize * y) + ((x + 1 + gridSize) % gridSize);

	int south_east = (gridSize * ((y + 1 + gridSize) % gridSize)) +
		((x + 1 + gridSize) % gridSize);

	int south = (gridSize * ((y + 1 + gridSize) % gridSize)) + x;

	int south_west = (gridSize * ((y + 1 + gridSize) % gridSize)) +
		((x - 1 + gridSize) % gridSize);

	int west = (gridSize * y) + ((x - 1 + gridSize) % gridSize);

	int north_west = (gridSize * ((y - 1 + gridSize) % gridSize)) +
		((x - 1 + gridSize) % gridSize);

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

// Sets the colour of a cell specified by index.
sf::Color BriansBrain::paint(int index)
{
	sf::Color colour;

	switch (population[index])
	{
		case on:
		{
			colour = sf::Color::Blue;
			break;
		}

		case dying:
		{
			colour = sf::Color::White;
			break;
		}

		default:
		{
			colour = sf::Color::Black;
			break;
		}
	}

	return colour;
}
