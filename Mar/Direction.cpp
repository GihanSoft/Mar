#include "Direction.h"

bool IsOpposite(Direction a, Direction b)
{
	auto h = (int)a ^ (int)b;
	if (h / 2 == 0 && h % 2 == 1)
		return true;
	return false;
}
