#ifndef  APPLICATION_H
#define  APPLICATION_H

#include "Util/config.h"
#include "cellularautomata.h"

class Application
{
private:
	int running = 1;
	double zoom = windowSize;
	double scale = windowSize / zoom;
	double update_step = 0.1;

	sf::RenderWindow window;
	sf::View view;

	std::vector<sf::Vertex> quads;

public:
	Application() {};

	CellularAutomata cellularAutomaton;

	void addQuads();
	void setQuadColour(sf::Color, int);

	void pollEvents();
	void input();

	void edit(sf::Vector2i);

	void run();
};

#endif //APPLICATION_H