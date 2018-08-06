#ifndef  APPLICATION_H
#define  APPLICATION_H

#include "Util/config.h"

#include "Game of Life/gameoflife.h"
#include "Brians Brain/briansbrain.h"

class Application
{
private:
	sf::RenderWindow window;

	std::vector<sf::Vertex> quads;

public:
	void addQuads();
	void setQuadColour(sf::Color, int);

	void pollEvents();

	template <typename T>
	void run(T &cellularAutomata)
	{
		window.create(sf::VideoMode(windowSize, windowSize), cellularAutomata.getName() , sf::Style::Titlebar | sf::Style::Close);
		window.setFramerateLimit(60);

		addQuads();

		cellularAutomata.init();

		while (window.isOpen())
		{
			pollEvents();

			window.clear();

			cellularAutomata.update();

			for (int i = 0; i < cellCount; i++)
			{
				setQuadColour(cellularAutomata.paint(i), i);
			}

			window.draw(quads.data(), quads.size(), sf::Quads);

			window.display();
		}
	}
};

#endif //APPLICATION_H