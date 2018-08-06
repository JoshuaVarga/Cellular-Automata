#ifndef  GAMEOFLIFE_H
#define  GAMEOFLIFE_H

#include "../Util/config.h"
#include "../Util/random.h"
#include <windows.h>

class GameOfLife
{
private:
	enum cell
	{
		on,
		off
	};

	std::vector<cell> population;

public:
	void init();
	void update();

	int countNeighbours(int);
	sf::Color paint(int);
};

#endif //GAMEOFLIFE_H
