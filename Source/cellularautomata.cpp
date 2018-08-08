#include "cellularautomata.h"

CellularAutomata::CellularAutomata(std::string rules)
{
	setName(rules);
}

void CellularAutomata::setName(std::string rules)
{
	name = rules;

	bool state = true;

	for (size_t i = 1; i < rules.length(); i++)
	{
		switch (state)
		{
		case true:
		{
			if (rules[i] == '/')
			{
				state = false;
				i++;
				break;
			}

			birth.push_back(rules[i] - '0');
			break;
		}

		case false:
		{
			survival.push_back(rules[i] - '0');
		}
		}
	}
}

std::string CellularAutomata::getName()
{
	return name;
}

void CellularAutomata::init()
{
	int percent;
	srandom();

	for (int i = 0; i < cellCount; i++)
	{
		percent = random(1, 100);

		if (percent > 66)
		{
			population.push_back(on);
		}

		else
		{
			population.push_back(off);
		}
	}
}

void CellularAutomata::update()
{
	std::vector<cell> new_population(cellCount);
	int neighbours;

	for (int i = 0; i < cellCount; i++)
	{
		neighbours = countNeighbours(i);

		new_population[i] = off;

		switch (population[i])
		{
			case on:
			{
				for (size_t j = 0; j < survival.size(); j++)
				{
					if (neighbours == survival[j])
					{
						new_population[i] = on;
					}
				}

				break;
			}

			default:
			{
				for (size_t j = 0; j < birth.size(); j++)
				{
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

void CellularAutomata::editCell(int x, int y)
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

int CellularAutomata::countNeighbours(int index)
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

sf::Color CellularAutomata::paint(int index)
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
