#ifndef  GAMEOFLIFE_H
#define  GAMEOFLIFE_H

#include "../Util/config.h"
#include "../Util/random.h"
#include <windows.h>

class GameOfLife
{
private:
	std::string name = "Game of Life";

	enum cell
	{
		on,
		off
	};

	std::vector<cell> population;

public:
	std::string getName();

	void init();
	void update();

	int countNeighbours(int);
	sf::Color paint(int);
};

#endif //GAMEOFLIFE_H