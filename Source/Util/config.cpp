#include "config.h"

int getX(int index)
{
	return index % gridSize;
}

int getY(int index)
{
	return index / gridSize;
}