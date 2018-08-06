#ifndef  CONFIG_H
#define  CONFIG_H

#include <iostream>
#include <vector>

#include <SFML/Graphics.hpp>

class Application;
class GameOfLife;

const int windowSize = 800;
const int cellSize = 2;
const int gridSize = windowSize / cellSize;
const int cellCount = gridSize * gridSize;

int getX(int);
int getY(int);

#endif //CONFIG_H
