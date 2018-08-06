#include "random.h"

int random(int min, int max)
{
	srand((unsigned int)time(NULL));
	return rand() % max + min;
}
