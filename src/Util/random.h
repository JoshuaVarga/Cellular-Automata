/**
	random.h
	Purpose: Generating random integers.

	@author Joshua Varga
	@Version 1.0
*/

#ifndef  RANDOM_H
#define  RANDOM_H

#include <stdlib.h>
#include <time.h>

/**
	Sets a seed for rand() based on the current system time.
*/
void srandom();

/**
	Returns a random integer between between min and max.

	@param min Minimum possible integer.
	@param max Maximum possible integer.
	@return    Random integer between between min and max.
*/
int random(int min, int max);

#endif //RANDOM_H

