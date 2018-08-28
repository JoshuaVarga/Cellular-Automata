/**
	custom.h
	Purpose: Implement a custom cellular automaton.

	@author Joshua Varga
	@version 1.0
*/

#ifndef  CUSTOM_H_
#define  CUSTOM_H_

#include "../cellularautomaton.h"

class Custom : public CellularAutomaton
{
private:
	std::string name;
	int populationSize = 0;
	int generation = 0;

	std::vector<int> birth;    // Stores neighbours needed for cell birth.
	std::vector<int> survival; // Stores neighbours needed for cell survival.

	enum cell
	{
		on,
		off
	};

	std::vector<cell> population;

public:
	/**
		Sets the name of the cellular automaton.

		@param name Desired name for the cellular automaton.
	*/
	void setName(std::string name) override;

	/**
		Gets the name of the cellular automaton.

		@return name of the cellular automaton.
	*/
	std::string getName() override;

	/**
		Generates random states states for the first generation of cells.
		Also prompts user for rules.
	*/
	void init() override;

	/**
		Replaces the current population with the next generation of cells.
	*/
	void update() override;

	/**
		Cycles the state of a cell at specific coordinates.

		@param x X coordinate of the cell.
		@param y Y coordinate of the cell.
	*/
	void cycleCell(int x, int y) override;

	/**
		Counts the neighbours in the Moore neighbourhood.

		@param index Index of the cell.
	*/
	int countNeighbours(int index) override;

	/**
		Sets the colour of a cell specified by index.

		@param index Index of a cell.
	*/
	sf::Color paint(int index) override;
};

#endif //CUSTOM_H_