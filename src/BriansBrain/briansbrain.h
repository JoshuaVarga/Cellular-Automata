/**
briansbrain.h
Purpose: Implement Brian's Brain cellular automaton.

@author Joshua Varga
@version 2.0
*/

#ifndef  BRIANSBRAIN_H_
#define  BRIANSBRAIN_H_

#include "../cellularautomaton.h"

class BriansBrain : public CellularAutomaton
{
private:
	std::string name = "Brian's Brain";
	int populationSize = 0;
	int generation = 0;

	enum cell
	{
		on,
		dying,
		off
	};

	std::vector<cell> population;
	std::vector<cell> new_population;

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
	*/
	void init() override;

	/**
		Replaces the current population with the next generation of cells.
	*/
	void update() override;

	/**
		Initializes information about the automaton.
	*/
	void initInfo() override;

	/**
		Updates automaton information.
	*/
	void updateInfo() override;

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

#endif //BRIANSBRAIN_H_