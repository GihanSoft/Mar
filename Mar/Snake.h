#pragma once
#include <list>
#include "Direction.h"
#include "Food.h"
#include <array>

using namespace std;

typedef void(*LooseFunc)();

class Snake
{
	list<COORD>* body;
	Direction direction;
public:
	COORD* GetBody(size_t & size);
	Direction GetDirection();
	void SetDirection(Direction);
	COORD GetNextPlace();
	void Move(bool eated = false);
	Snake();
	~Snake();
};
