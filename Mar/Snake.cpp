#include "Snake.h"

COORD * Snake::GetBody(size_t & size)
{
	auto count = body->size();

	auto bodyArray = new COORD[count];
	auto it = this->body->begin();
	for (size_t i = 0; i < this->body->size(); i++, it++)
	{
		bodyArray[i] = *it;
	}
	size = count;
	return bodyArray;
}

Direction Snake::GetDirection()
{
	return Direction(direction);
}

void Snake::SetDirection(Direction direction)
{
	if (IsOpposite(this->direction, direction))
		return;
	this->direction = direction;
}

COORD Snake::GetNextPlace()
{
	auto Head = body->front();
	COORD newPlace = Head;

	switch (direction)
	{
	case Direction::Up:
		newPlace.Y--;
		break;
	case Direction::Down:
		newPlace.Y++;
		break;
	case Direction::Right:
		newPlace.X++;
		break;
	case Direction::Left:
		newPlace.X--;
		break;
	default:
		break;
	}
	return newPlace;
}

void Snake::Move(bool eated)
{
	auto newPlace = GetNextPlace();
	body->push_front(newPlace);
	if (!eated)
		body->pop_back();
}

Snake::Snake()
{
	this->body = new list<COORD>();
	this->direction = Direction::Right;

	COORD b[3] = { COORD{2,2}, COORD{3,2}, COORD{4,2} };

	for (int i = 0; i < 3; i++)
	{
		body->push_front(b[i]);
	}
}


Snake::~Snake()
{
	delete this->body;
}
