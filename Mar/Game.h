#pragma once
#include <iostream>
#include "UI.h"
#include "Keyboard.h"

class Game
{
	Snake* _snake;
	Snake* _snake2;

	Food* _food;
	Food* _food2;
	UI* _ui;
	Keyboard* _keyboard;

	int _n;

	int last1;
	int last2;

	void Hit();
	void DHit(int, bool);
	void SnakeMoved();

public:
	Game(int);
	void Run();
	~Game();
};

bool operator== (COORD a, COORD b);