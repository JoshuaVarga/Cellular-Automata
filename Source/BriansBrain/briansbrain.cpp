/**
briansbrain.cpp
Purpose: Implement Brian's Brain cellular automaton.

@author Joshua Varga
@version 2.0
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

// Generates random states states for the first generation of cells and initializes information..
void BriansBrain::init()
{
	for (int i = 0; i < cellCount; i++)
	{
		// All cells begin off.
		population.get()->push_back(off);
	}
}

// Replaces the current population with the next generation of cells.
void BriansBrain::update()
{
	// Next generation.
	generation++;
	
	int neighbours;

	// Loop through all cells and change their state in the next generation based on neighbours.
	for (int i = 0; i < cellCount; i++)
	{
		switch (population.get()->at(i))
		{
			case on:
			{
				new_population.get()->at(i) = dying;
				break;
			}

			case dying:
			{
				new_population.get()->at(i) = off;
				populationSize--;
				break;
			}

			default:
			{			
				neighbours = countNeighbours(i);

				switch (neighbours)
				{
					case 2:
					{
						new_population.get()->at(i) = on;
						populationSize++;
						break;
					}

					default:
					{
						new_population.get()->at(i) = off;
						break;
					}
				}
			}
		}
	}

	population.swap(new_population);
}

// Initializes information about the automaton.
void BriansBrain::initInfo()
{
	// Resize to the amount of info.
	information.resize(2);

	// Set the title of the info.
	information[0].title = "Population";
	information[1].title = "Generation";
}

// Updates automaton information.
void BriansBrain::updateInfo()
{
	information[0].value = std::to_string(populationSize);
	information[1].value = std::to_string(generation);
}

// Cycles the state of a cell at specific coordinates.
void BriansBrain::cycleCell(int x, int y)
{
	if (x < 0 || x > windowSize)
	{
		return;
	}

	int index = getIndex(x / cellSize, y / cellSize);

	switch (population.get()->at(index))
	{
		case on:
		{
			population.get()->at(index) = dying;
			break;
		}

		case dying:
		{
			population.get()->at(index) = off;
			populationSize--;
			break;
		}

		case off:
		{
			population.get()->at(index) = on;
			populationSize++;
			break;
		}
	}
}

// Counts the neighbours in the Moore neighbourhood. 
// TODO: Increase performance.
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

	if (population.get()->at(north) == on)      neighbours++;
	if (population.get()->at(north_east) == on) neighbours++;
	if (population.get()->at(east) == on)       neighbours++;
	if (population.get()->at(south_east) == on) neighbours++;
	if (population.get()->at(south) == on)      neighbours++;
	if (population.get()->at(south_west) == on) neighbours++;
	if (population.get()->at(west) == on)       neighbours++;
	if (population.get()->at(north_west) == on) neighbours++;

	return neighbours;
}

// Sets the colour of a cell specified by index.
sf::Color BriansBrain::paint(int index)
{
	switch (population.get()->at(index))
	{
		case on:
		{
			return sf::Color::Blue;
		}

		case dying:
		{
			return sf::Color::White;
		}

		default:
		{
			return sf::Color::Black;
		}
	}
}
