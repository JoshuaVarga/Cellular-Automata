#include "Game of Life/gameoflife.h"
#include "application.h"


int main()
{
	Application application;
	GameOfLife cellularAutomata;

	application.run(cellularAutomata);

	return 0;
}
