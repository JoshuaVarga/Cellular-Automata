#ifndef  GAMEOFLIFE_H
#define  GAMEOFLIFE_H

#include "../application.h"

class GameOfLife
{
private:
	enum cell
	{
		on,
		off
	};

	std::vector<cell> data;

public:
	void init();
	void evolve();

	void update(Application &);
	void rePaint(Application &);

	int countNeighbours(int);
};

#endif //GAMEOFLIFE_H
