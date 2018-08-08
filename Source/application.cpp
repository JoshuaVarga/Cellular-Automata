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
					case sf::Keyboard::Z:
					{
						if ((1 / update_step) > 2)
						{
							update_step += (1 / (1 / update_step - 1)) - (1 / (1 / update_step));
						}
						break;
					}

					case sf::Keyboard::X:
					{
						if ((1 / update_step) < 60)
						{
							update_step -= (1 / (1 / update_step)) - (1 / (1 / update_step + 1));
						}
						break;
					}

					case sf::Keyboard::R:
					{
						zoom = windowSize;
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

			case (sf::Event::MouseButtonPressed):
			{
				switch (event.mouseButton.button)
				{
					case(sf::Mouse::Left):
					{
						if (running < 0)
						{
							edit(sf::Mouse::getPosition(window));
						}
					}
				}
				break;
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

			zoom -= 10;
			scale = windowSize / zoom;
			view.setSize(scale * windowSize, scale * windowSize);
		
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
			zoom += 10;
			scale = windowSize / zoom;
			std::cout << (scale * windowSize) << std::endl;
			view.setSize(scale * windowSize, scale * windowSize);
	
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0, -10 * (1 / scale));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(10 * (1 / scale), 0);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(0, 10 * (1 / scale));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(-10 * (1 / scale), 0);
	}
}

void Application::edit(sf::Vector2i vector)
{
	cellularAutomaton.editCell(vector.x, vector.y);
}

void Application::run()
{
	std::cout << "Controls:\n"
		<< "Q/E   - Zoom\n"
		<< "WASD  - Pan camera\n"
		<< "R     - Reset camera\n"
		<< "Z/X   - Change simulation speed\n"
		<< "Space - Pause\n"
		<< "Esc   - Exit\n"
		<< "__________________________________________________\n\n";

	window.create(sf::VideoMode(windowSize, windowSize), cellularAutomaton.getName(), sf::Style::Titlebar | sf::Style::Close);
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
			}

			total_time -= update_step;
		}

		window.clear();

		window.setView(view);

		for (int i = 0; i < cellCount; i++)
		{
			setQuadColour(cellularAutomaton.paint(i), i);
		}

		window.draw(quads.data(), quads.size(), sf::Quads);

		window.display();
	}
}


