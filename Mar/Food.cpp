#include "Food.h"

COORD Food::GetLocation()
{
	return COORD(Location);
}

void Food::PutNew()
{
	this->Location.X = rand() % d + 1;
	this->Location.Y = rand() % d + 1;
}

Food::Food(int dd)
	:d(dd)
{
	srand((unsigned)time(0));
}


Food::~Food()
{
}
