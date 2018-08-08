#ifndef  CELLULARAUTOMATA_H
#define  CELLULARAUTOMATA_H

#include "Util/config.h"
#include "Util/random.h"
#include <windows.h>

class CellularAutomata
{
private:
	std::string name;

	std::vector<int> birth;
	std::vector<int> survival;

	enum cell
	{
		on,
		off
	};

	std::vector<cell> population;

public:
	CellularAutomata() {};

	CellularAutomata(std::string);

	void setName(std::string);
	std::string getName();

	void init();
	void update();

	void editCell(int, int);

	int countNeighbours(int);
	sf::Color paint(int);
};

#endif //CELLULARAUTOMATA_H