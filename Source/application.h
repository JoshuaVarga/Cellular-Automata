#ifndef  APPLICATION_H
#define  APPLICATION_H

#include "Util/config.h"
#include "Game of Life/gameoflife.h"

class Application
{
private:
	sf::RenderWindow window;

	std::vector<sf::Vertex> quads;

public:
	void addQuads();
	void setQuadColour(sf::Color, int);

	void pollEvents();
	void run(GameOfLife &);
};

#endif //APPLICATION_H