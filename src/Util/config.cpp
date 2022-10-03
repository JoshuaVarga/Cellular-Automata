#include "config.h"

int getIndex(int x, int y)
{
	return (y * gridSize) + x;
}

int getX(int index)
{
	return index % gridSize;
}

int getY(int index)
{
	return index / gridSize;
}