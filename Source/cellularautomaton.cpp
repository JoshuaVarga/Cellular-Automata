/**
cellularautomaton.cpp
Purpose: TODO

@author Joshua Varga
@version 1.0
*/

#include "cellularautomaton.h"

CellularAutomaton::CellularAutomaton(std::string rules)
{
	setName(rules);
}

// Sets the name of the cellular automaton.
void CellularAutomaton::setName(std::string rules)
{
	// Rules in form: Bbbbbbbbb/Sssssssss.
	// Left side of slash is birth conditions and right is survival consitions.
	// ex. B3/S23
	name = rules;

	// True to push rules to birth array
	bool state = true;

	// Start index at one to skip 'B'.
	for (size_t i = 1; i < rules.length(); i++)
	{
		switch (state)
		{
			case true:
			{
				if (rules[i] == '/')
				{
					state = false; // False to push rules to survival array.
					i++;		   // Incriment index by one to skip 'S'.
					break;
				}

				// Add rule to birth array as integer.
				birth.push_back(rules[i] - '0');
				break;
			}

			case false:
			{
				// Add rule to survival array as integer.
				survival.push_back(rules[i] - '0');
				break;
			}
		}
	}
}

// Gets the name of the cellular automaton.
std::string CellularAutomaton::getName()
{
	return name;
}

// Generates random states states for the first generation of cells.
void CellularAutomaton::init()
{
	int percent;
	srandom();

	// Loop through cells and set them to on or off randomly.
	for (int i = 0; i < cellCount; i++)
	{
		percent = random(1, 100);

		if (percent > 69)
		{
			population.push_back(on);
		}

		else
		{
			population.push_back(off);
		}
	}
}

// Replaces the current population with the next generation of cells.
void CellularAutomaton::update()
{
	// Next generation.
	std::vector<cell> new_population(cellCount);

	int neighbours;

	// Loop through all cells and change their state in the next generation based on neighbours.
	for (int i = 0; i < cellCount; i++)
	{
		neighbours = countNeighbours(i);

		// Assume the cell is off until proven otherwise.
		new_population[i] = off;

		switch (population[i])
		{
			case on:
			{
				for (size_t j = 0; j < survival.size(); j++)
				{
					// Cell stays on if neighbours match rules.
					if (neighbours == survival[j])
					{
						new_population[i] = on;
					}
				}

				break;
			}

			// case off:
			default:
			{
				for (size_t j = 0; j < birth.size(); j++)
				{
					// Cell turns on if neighbours match rules.
					if (neighbours == birth[j])
					{
						new_population[i] = on;
					}
				}
				break;
			}
		}
	}

	population = new_population;
}

// Cycles the state of a cell at specific coordinates.
void CellularAutomaton::cycleCell(int x, int y)
{
	int index = getIndex(x, y);

	switch (population[index])
	{
		case on:
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
int CellularAutomaton::countNeighbours(int index)
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
sf::Color CellularAutomaton::paint(int index)
{
	sf::Color colour;

	if (population[index] == on)
	{
		colour = sf::Color::White;
	}

	else
	{
		colour = sf::Color::Black;
	}

	return colour;
}
