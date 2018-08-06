#ifndef  CONFIG_H
#define  CONFIG_H

#include <vector>

const int windowSize = 512;
const int cellSize = 4;
const int gridSize = windowSize / cellSize;
const int cellCount = gridSize * gridSize;

float getX(int);
float getY(int);

#endif //CONFIG_H
