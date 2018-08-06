#include "application.h"

void Application::addQuads()
{
	float x, y;

	sf::Vertex topLeft, topRight, bottomRight, bottomLeft;
	
	for (int i = 0; i < cellCount; i++)
	{
		x = (float)cellSize * getX(i);
		y = (float)cellSize * getY(i);

		topLeft.position     = { x           , y            };
		topRight.position    = { x + cellSize, y            };
		bottomRight.position = { x + cellSize, y + cellSize };
		bottomLeft.position  = { x           , y + cellSize };

		quads.push_back(topLeft);
		quads.push_back(topRight);
		quads.push_back(bottomRight);
		quads.push_back(bottomLeft);
	}
}

void Application::setQuadColour(sf::Color colour, int index)
{
	for (int i = 0; i < 4; i++)
	{
		quads[index * 4 + i].color = colour;
	}
}

void Application::pollEvents()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
			case (sf::Event::Closed):
			{
				window.close();
				break;
			}

			case (sf::Event::KeyPressed):
			{
				switch (event.key.code)
				{
					case sf::Keyboard::R:
					{
						view.reset(sf::FloatRect(0, 0, windowSize, windowSize));
						break;
					}

					case sf::Keyboard::Space:
					{
						running *= -1;
						break;
					}

					case sf::Keyboard::Escape:
					{
						window.close();
					}

					default:
					{
						break;
					}
				}
			}

			default:
			{
				break;
			}
		}
	}
}

void Application::input()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		zoom *= 1.1;
		view.zoom(1.1);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		zoom *= 0.9;
		view.zoom(0.9);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0, -1 * zoom);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(zoom, 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(0, zoom);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(-1 * zoom, 0);
	}
}

