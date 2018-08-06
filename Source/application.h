#ifndef  APPLICATION_H
#define  APPLICATION_H

#include "Util/config.h"

#include <SFML/Graphics.hpp>

class Application
{
private:
	sf::RenderWindow window;

	std::vector<sf::Vertex> quads;

public:
	void addQuads();

	void setQuadColour(sf::Color, int);

	void pollEvents();

	template <typedef T>
	void run(T);
};

#endif //APPLICATION_H