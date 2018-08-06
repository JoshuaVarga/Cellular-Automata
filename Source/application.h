#ifndef  APPLICATION_H
#define  APPLICATION_H

#include "Util/config.h"

#include "Game of Life/gameoflife.h"
#include "Brians Brain/briansbrain.h"

class Application
{
private:
	int running = 1;
	float zoom = 10;

	sf::RenderWindow window;
	sf::View view;

	std::vector<sf::Vertex> quads;

public:
	void addQuads();
	void setQuadColour(sf::Color, int);

	void pollEvents();
	void input();

	template <typename T>
	void run(T &cellularAutomaton)
	{
		window.create(sf::VideoMode(windowSize, windowSize), cellularAutomaton.getName() , sf::Style::Titlebar | sf::Style::Close);
		window.setFramerateLimit(60);

		view.reset(sf::FloatRect(0, 0, windowSize, windowSize));

		addQuads();

		cellularAutomaton.init();

		while (window.isOpen())
		{
			pollEvents();

			input();

			if (running > 0)
			{
				cellularAutomaton.update();

				for (int i = 0; i < cellCount; i++)
				{
					setQuadColour(cellularAutomaton.paint(i), i);
				}
			}

			window.clear();

			window.setView(view);

			window.draw(quads.data(), quads.size(), sf::Quads);

			window.display();
		}
	}
};

#endif //APPLICATION_H