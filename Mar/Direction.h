#pragma once

enum class Direction
{
	Up = 0b00,
	Down = 0b01,
	Right = 0b10,
	Left = 0b11
};

bool IsOpposite(Direction a, Direction b);