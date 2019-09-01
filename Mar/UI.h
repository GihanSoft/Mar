#pragma once
#include <string>
#include "Snake.h"
#include "Food.h"
#include "conio21\conio2.h"

class UI
{
	const int BoardStartX = 4;
	const int BoardStartY = 3;

	const int BoardHeight;
	const int BoardWidth;
	const COORD BoardStart;
	const COORD BoardEnd;

	Snake* _snake;
	Snake* _snake2;
	Food* _food;
	Food* _food2;

	COORD ConvertCoord(COORD);

	void RenderBoard(int score1, int score2);
	void RenderSnake(Snake*);
	void RenderFood(Food*);
public:
	UI(Snake*, Food*, Snake*, Food*, int boardHeight = 30, int boardWidth = 30);

	void Render(int score, int score2);

	void SnakeRemove(int snakeNum);

	~UI();
};

