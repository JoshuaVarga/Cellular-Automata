/**
cellularautomaton.h
Purpose: Implement a cellular automaton.

@author Joshua Varga
@version 1.0
*/

#ifndef  CELLULARAUTOMATON_H_
#define  CELLULARAUTOMATON_H_

#include "Util/config.h"
#include "Util/random.h"
#include <windows.h>

class CellularAutomaton
{
private:
	std::string name;

	std::vector<int> birth;    // Stores neighbours needed for cell birth.
	std::vector<int> survival; // Stores neighbours needed for cell survival.

	enum cell
	{
		on,
		off
	};

	// All Cells within the simulation.
	std::vector<cell> population;

public:
	CellularAutomaton() {};

	CellularAutomaton(std::string);
	
	/**
		Sets the name of the cellular automaton.

		@param name Desired name for the cellular automaton.
	*/
	void setName(std::string name);

	/**
		Gets the name of the cellular automaton.

		@return name of the cellular automaton.
	*/
	std::string getName();

	/**
		Generates random states states for the first generation of cells.
	*/
	void init();

	/**
		Replaces the current population with the next generation of cells.
	*/
	void update();

	/**
		Cycles the state of a cell at specific coordinates.

		@param x X coordinate of the cell.
		@param y Y coordinate of the cell.
	*/
	void cycleCell(int x, int y);

	/**
		Counts the neighbours in the Moore neighbourhood. 

		@param index Index of the cell.
	*/
	int countNeighbours(int index);

	/**
		Sets the colour of a cell specified by index.

		@param index Index of a cell.
	*/
	sf::Color paint(int index);
};

#endif //CELLULARAUTOMATON_H_