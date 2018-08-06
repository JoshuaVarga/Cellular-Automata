#ifndef  BRIANSBRAIN_H
#define  BRIANSBRAIN_H

#include "../Util/config.h"
#include "../Util/random.h"
#include <windows.h>

class BriansBrain
{
private:
	std::string name = "Brian's Brain";

	enum cell
	{
		on,
		dying,
		off
	};

	std::vector<cell> population;

public:
	std::string getName();

	void init();
	void update();

	int countNeighbours(int);
	sf::Color paint(int);
};

#endif //BRIANSBRAIN_H
