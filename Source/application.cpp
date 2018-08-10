/**
application.cpp
Purpose: TODO

@author Joshua Varga
@version 1.0
*/

#include "application.h"

// Fills array with vertices by cell index for drawing cells.
void Application::addQuads()
{
	// Coordinates
	float x, y;

	sf::Vertex topLeft, topRight, bottomRight, bottomLeft;
	
	for (int i = 0; i < cellCount; i++)
	{
		// Scale the array coordinates to match window coordinates.
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

// Sets the colour of a cell by index to the specified colour.
void Application::setQuadColour(sf::Color colour, int index)
{
	// There are four vertices per cell.
	for (int i = 0; i < 4; i++)
	{
		quads[index * 4 + i].color = colour;
	}
}

// Cycles the state of a cell at specific coordinates.
void Application::cycleCell(sf::Vector2i coordinates)
{
	cellularAutomaton.cycleCell(coordinates.x, coordinates.y);
}

// Checks and handles events.
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

			// Non repeating key input.
			case (sf::Event::KeyPressed):
			{
				switch (event.key.code)
				{
					// Increase interval between updates.
					case sf::Keyboard::Z:
					{
						// (1 / update_interval) is update_interval as frames.
						if ((1 / update_interval) > 1)
						{
							// Time difference between previous interval and current.
							update_interval += (1 / (1 / update_interval - 1)) -
								(1 / (1 / update_interval));

							std::cout << 1 / update_interval << std::endl;
						}
						break;
					}

					// Decrease interval between updates.
					case sf::Keyboard::X:
					{
						if (running < 0)
						{
							cellularAutomaton.update();
							break;
						}

						// (1 / update_interval) is update_interval as frames.
						if ((1 / update_interval) < 60)
						{
							// Time difference between next interval and current.
							update_interval += (1 / (1 / update_interval + 1)) -
								(1 / (1 / update_interval));

							std::cout << 1 / update_interval << std::endl;
						}
						break;
					}

					// Reset zoom and view to it's initial state.
					case sf::Keyboard::R:
					{
						view.reset(sf::FloatRect(0, 0, windowSize, windowSize));
						break;
					}

					// Pause updates.
					case sf::Keyboard::Space:
					{
						running *= -1;
						break;
					}

					// Close applicatoin.
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

			// Non repeating mouse input.
			case (sf::Event::MouseButtonPressed):
			{
				switch (event.mouseButton.button)
				{
					// Switches the state of a cell.
					case(sf::Mouse::Left):
					{
						if (running < 0)
						{
							cycleCell(sf::Mouse::getPosition(window));
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

// Handles keyboard and mouse input.
void Application::input()
{
	// Zoom view out.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
	{
		view.zoom(1.01f);
	}

	// Zoom view in.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		view.zoom(0.99f);
	}

	// Pan view up.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		view.move(0, -1);
	}

	// Pan view right.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		view.move(1, 0);
	}

	// Pan view down.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		view.move(0, 1);
	}

	// Pan view left.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		view.move(-1, 0);
	}
}

// Runs the application.
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

	window.create(sf::VideoMode(windowSize, windowSize), 
		cellularAutomaton.getName(), sf::Style::Titlebar | sf::Style::Close);
	window.setFramerateLimit(60);
	window.setKeyRepeatEnabled(false);

	view.reset(sf::FloatRect(0, 0, windowSize, windowSize));

	addQuads();

	cellularAutomaton.init();

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

		std::cout << 1 / frame_time << "\b\b\b\b\b\b\b";

		pollEvents();

		input();

		window.setView(view);

		while (total_time >= update_interval)
		{
			if (running > 0)
			{
				cellularAutomaton.update();
			}

			total_time -= update_interval;
		}

		window.clear();

		for (int i = 0; i < cellCount; i++)
		{
			setQuadColour(cellularAutomaton.paint(i), i);
		}

		window.draw(quads.data(), quads.size(), sf::Quads);

		window.display();
	}
}


