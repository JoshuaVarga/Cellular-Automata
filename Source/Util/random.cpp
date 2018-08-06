#include "random.h"

void srandom()
{
	srand((unsigned int)time(NULL));
}

int random(int min, int max)
{
	return rand() % max + min;
}
