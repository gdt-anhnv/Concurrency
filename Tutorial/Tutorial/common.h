#ifndef _COMMON_H_
#define _COMMON_H_

#include <iostream>
#include <random>
#include <ctime>

int random()
{
	std::srand(std::time(nullptr));
	return std::rand() % 1000;
}

#endif