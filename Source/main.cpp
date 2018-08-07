#include "Game of Life/gameoflife.h"
#include "application.h"

int main()
{
	start:
	Application application;
	
	std::cout << "Choose a Cellular Automaton:\n"
			  << "[0] Exit\n"
			  << "[1] Game of Life\n"				
			  << "[2] Brian's Brain\n\n"			
			  << "Choice: ";

	int choice = 0;
	std::cin >> choice;

	std::cout << "__________________________________________________\n";

	switch (choice)
	{
	case 0:
	{
		return 0;
	}

	case 1:
	{
		GameOfLife cellularAutomaton;
		application.run(cellularAutomaton);
		break;
	}
	case 2:
	{
		BriansBrain cellularAutomaton;
		application.run(cellularAutomaton);
		break;
	}
	default:
		return 0;
	}

	goto start;

	return 0;
}
