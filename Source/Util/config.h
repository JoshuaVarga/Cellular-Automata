#ifndef  CONFIG_H
#define  CONFIG_H

#include <iostream>
#include <string>

#include <vector>

#include <SFML/Graphics.hpp>

const int windowSize = 800;				  // Width/Height of the window (pixels);
const int cellSize   = 4;					  // Width/Height of each individual cell (pixels).
const int gridSize   = windowSize / cellSize; // The amount of cells that fit side by side into the x or y dimension of the window.
const int cellCount  = gridSize * gridSize;   // Total amount of cells that fit into the window.

int getIndex(int, int);

int getX(int);
int getY(int);

#endif //CONFIG_H
