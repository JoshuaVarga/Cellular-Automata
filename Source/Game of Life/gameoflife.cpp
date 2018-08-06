#include "gameoflife.h"

void GameOfLife::init()
{
	for (int i = 0; i < cellCount; i++)
	{
		int percent = i;

		if (percent > 50)
		{
			data.push_back(on);
		}

		else
		{
			data.push_back(off);
		}
	}
}

void GameOfLife::evolve()
{
	for (int i = 0; i < cellCount; i++)
	{
		int neighbours = countNeighbours(i);

		if (data[i] == on)
		{
			if (neighbours < 2 || neighbours > 3)
			{
				data[i] = off;
			}
		}

		else
		{
			if (neighbours == 3)
			{
				data[i] = on;
			}
		}
	}
}

void GameOfLife::update(Application &application)
{
	evolve();
	rePaint(application);
}

void GameOfLife::rePaint(Application &application)
{
	for (int i = 0; i < cellCount; i++)
	{
		if (data[i] == on)
		{
			application.setQuadColour(sf::Color::White, i);
		}

		else
		{
			application.setQuadColour(sf::Color::Black, i);
		}
	}
}

int GameOfLife::countNeighbours(int index)
{
	int neighbours = 0;

	int x = (int)getX(index);
	int y = (int)getY(index);

	int north = (gridSize* ((y - 1 + gridSize) % gridSize)) + x;
	int north_east = (gridSize * ((y - 1 + gridSize) % gridSize)) + ((x + 1 + gridSize) % gridSize);
	int east = (gridSize * y) + ((x + 1 + gridSize) % gridSize);
	int south_east = (gridSize * ((y + 1 + gridSize) % gridSize)) + ((x + 1 + gridSize) % gridSize);
	int south = (gridSize * ((y + 1 + gridSize) % gridSize)) + x;
	int south_west = (gridSize * ((y + 1 + gridSize) % gridSize)) + ((x - 1 + gridSize) % gridSize);
	int west = (gridSize * y) + ((x - 1 + gridSize) % gridSize);
	int north_west = (gridSize * ((y - 1 + gridSize) % gridSize)) + ((x - 1 + gridSize) % gridSize);

	if (data[north] == on)      neighbours++;
	if (data[north_east] == on) neighbours++;
	if (data[east] == on)       neighbours++;
	if (data[south_east] == on) neighbours++;
	if (data[south] == on)      neighbours++;
	if (data[south_west] == on) neighbours++;
	if (data[west] == on)       neighbours++;
	if (data[north_west] == on) neighbours++;

	return neighbours;
}


