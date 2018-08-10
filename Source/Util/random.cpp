/**
random.cpp
Purpose: Generating random integers.

@author Joshua Varga
@Version 1.0
*/

#include "random.h"

//Sets a seed for rand() based on the current system time.
void srandom()
{
	srand((unsigned int)time(NULL));
}

//Generates a random integer between between min and max.
int random(int min, int max)
{
	return rand() % max + min;
}
