/*
	Nathan Harris
	8-18-16
*/

#include <cstdlib>
#include <ctime>

#include "Utility.h"

int RPG::GetRandomValue(const int between, const int and)
{
	std::srand(std::time(NULL));

	if (between + and == 0)
	{
		return 0;
	}
	else
	{
		return std::rand() % and +between;
	}
}