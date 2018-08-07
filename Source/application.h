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
	double update_step = 0.0166666666666666;

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
		std::cout << "Controls:\n"
			      << "Q/E   - Zoom\n"
				  << "WASD  - Pan camera\n"
				  << "R     - Reset camera\n"
				  << "Z/X   - Change simulation speed\n"
				  << "Space - Pause\n"
				  << "Esc   - Exit\n"
				  << "__________________________________________________\n\n";

		window.create(sf::VideoMode(windowSize, windowSize), cellularAutomaton.getName() , sf::Style::Titlebar | sf::Style::Close);
		window.setFramerateLimit(60);
		window.setKeyRepeatEnabled(false);

		view.reset(sf::FloatRect(0, 0, windowSize, windowSize));

		addQuads();

		cellularAutomaton.init();

		sf::Clock clock;

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

			pollEvents();

			input();

			while (total_time >= update_step)
			{
				if (running > 0)
				{
					cellularAutomaton.update();

					for (int i = 0; i < cellCount; i++)
					{
						setQuadColour(cellularAutomaton.paint(i), i);
					}
				}

				total_time -= update_step;
			}

			window.clear();

			window.setView(view);

			window.draw(quads.data(), quads.size(), sf::Quads);

			window.display();
		}
	}
};

#endif //APPLICATION_H