/**
	application.h
	Purpose: TODO

	@author Joshua Varga
	@version 1.0
*/

#ifndef  APPLICATION_H_
#define  APPLICATION_H_

#include "Util/config.h"
#include "cellularautomaton.h"

class Application
{
private:
	int running = 1; // Is the game updating? running > 0 = true, running < 0 = false.
	double update_interval = 0.1; // Time in seconds between game updates.

	sf::RenderWindow window;
	sf::View view;

	std::vector<sf::Vertex> quads; // Array to store vertices for each cell.

public:
	Application() {};

	CellularAutomaton cellularAutomaton;

	/**
		Fills array with vertices by cell index for drawing cells.
	*/
	void addQuads();

	/**
		Sets the colour of a cell by index to the specified colour.

		@param colour Colour to paint cell.
		@param index Index of cell in array.
	*/
	void setQuadColour(sf::Color colour, int index);

	/**
		Cycles the state of a cell at specific coordinates.

		@param coordinates x,y coordinates of the mouse.
	*/
	void cycleCell(sf::Vector2i coordinates);

	/**
		Checks and handles events.
	*/
	void pollEvents();

	/**
		Handles keyboard and mouse input.
	*/
	void input();

	/**
		Runs the application.
	*/
	void run();
};

#endif //APPLICATION_H_