/**
	application.h
	Purpose: Handles a window.

	@author Joshua Varga
	@version 2.0
*/

#ifndef  APPLICATION_H_
#define  APPLICATION_H_

#include <memory>

#include "Util/config.h"
#include "Custom/custom.h"
#include "BriansBrain/briansbrain.h"

class Application
{
private:
	int running = 1; // Is the game updating? running > 0 = true, running < 0 = false.
	double update_interval = 0.1; // Time in seconds between game updates.

	sf::Font font;
	std::vector<sf::Text> texts;

	sf::RenderWindow window;
	sf::View view;

	std::vector<sf::Vertex> quads; // Array to store vertices for each cell.

	std::unique_ptr<CellularAutomaton> cellularAutomaton;

public:
	Application() {};

	/**
		Changes the type of cellular automaton and initializes it.
	*/
	template <typename T>
	void init()
	{
		cellularAutomaton = std::make_unique<T>();
		cellularAutomaton->init();
	}

	/**
		Initializes the GUI.
	*/
	void initGUI();

	/**
		Updates the GUI.
	*/
	void updateGUI();

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
	void cycleCell(sf::Vector2f coordinates);

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
	template <typename T>
	void run()
	{
		std::cout << "Controls:\n"
			<< "Q/E   - Zoom\n"
			<< "WASD  - Pan camera\n"
			<< "R     - Reset camera\n"
			<< "Z/X   - Change simulation speed\n"
			<< "Space - Pause\n"
			<< "Esc   - Exit\n"
			<< "__________________________________________________\n\n";

		init<T>();	
		initGUI();

		window.create(sf::VideoMode(windowSize, windowSize),
			cellularAutomaton->getName(), sf::Style::Titlebar | sf::Style::Close);
		window.setFramerateLimit(60);
		window.setVerticalSyncEnabled(false);
		window.setKeyRepeatEnabled(false);

		view.reset(sf::FloatRect(0, 0, windowSize, windowSize));

		addQuads();

		sf::Clock clock;

		// For frame independant updating.
		double total_time = 0;
		double current_time = clock.getElapsedTime().asSeconds();
		double new_time;
		double frame_time;

		while (window.isOpen())
		{
			new_time = clock.getElapsedTime().asSeconds();
			frame_time = new_time - current_time;
			current_time = new_time;
			total_time += frame_time;

			//std::cout << 1 / frame_time << "\b\b\b\b\b\b\b";

			pollEvents();

			input();

			window.clear();

			while (total_time >= update_interval)
			{
				if (running > 0)
				{
					cellularAutomaton->update();
				}

				total_time -= update_interval;
			}

			updateGUI();

			for (int i = 0; i < cellCount; i++)
			{
				setQuadColour(cellularAutomaton->paint(i), i);
			}

			window.setView(view);

			window.draw(quads.data(), quads.size(), sf::Quads);
			
			window.setView(window.getDefaultView());
				
			for (int i = 0; i < texts.size(); i++)
			{
				window.draw(texts[i]);
			}

			window.display();
		}
	}
};

#endif //APPLICATION_H_