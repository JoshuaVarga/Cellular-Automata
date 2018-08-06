#include "config.h"

float getX(int index)
{
	return (float)(cellSize * (index % gridSize));
}

float getY(int index)
{
	return (float)(cellSize * (index / gridSize));
}
