/**
cellularautomaton.h
Purpose: Parent class for all cellular automata.

@author Joshua Varga
@version 2.0
*/

#ifndef  CELLULARAUTOMATON_H_
#define  CELLULARAUTOMATON_H_

#include "Util/config.h"
#include "Util/random.h"

class CellularAutomaton
{
public:
	CellularAutomaton(){};

	struct info
	{
		std::string title;
		std::string value;
	};

	std::vector<info> information;

	// Overridden in child classes.
	virtual void setName(std::string name) {};
	virtual std::string getName() { return NULL;};
	virtual void init() {};
	virtual void update() {};
	virtual void initInfo() {};
	virtual void updateInfo() {};
	virtual void cycleCell(int x, int y) {};
	virtual int countNeighbours(int index) { return NULL; };
	virtual sf::Color paint(int index) { return (sf::Color)NULL; };
};

#endif //CELLULARAUTOMATON_H_