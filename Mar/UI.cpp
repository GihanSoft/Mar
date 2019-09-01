#include "UI.h"



COORD UI::ConvertCoord(COORD coord)
{
	return COORD() = { coord.X + BoardStart.X, coord.Y + BoardStart.Y };
}

void UI::RenderBoard(int score1, int score2)
{
	gotoxy(1, 1);
	textbackground(COLORS::BLACK);
	textcolor(COLORS::LIGHTGRAY);
	_cputs("Snake Game\n");
	if (_snake2 == nullptr) {
		_cputs("Your score is : ");
		_cputs(std::to_string(score1).c_str());
	}
	else if (_snake == nullptr) {
		_cputs("Your score is : ");
		_cputs(std::to_string(score2).c_str());
	}
	else
	{
		_cputs("Player1 score : ");
		_cputs(std::to_string(score1).c_str());
		_cputs("\t");
		_cputs("Player2 score : ");
		_cputs(std::to_string(score2).c_str());
	}

	textbackground(COLORS::WHITE);
	short x = BoardStart.X;
	short y = BoardStart.Y;
	for (; x <= BoardEnd.X; x++)
	{
		gotoxy(x, y);
		_putch(0);
	}
	for (; y <= BoardEnd.Y; y++)
	{
		gotoxy(x, y);
		_putch(0);
	}
	for (; x >= BoardStart.X; x--)
	{
		gotoxy(x, y);
		_putch(0);
	}
	for (; y >= BoardStart.Y; y--)
	{
		gotoxy(x, y);
		_putch(0);
	}
	textbackground(COLORS::BLACK);
}

void UI::RenderSnake(Snake* snake)
{
	if (snake == nullptr)
		return;

	size_t n;
	auto body = snake->GetBody(n);

	auto p = ConvertCoord(body[0]);
	gotoxy(p.X, p.Y);
	textbackground(COLORS::BLACK);
	textcolor(COLORS::WHITE);
	if (snake == _snake2) {
		textcolor(COLORS::LIGHTCYAN);
	}
	_putch('@');

	for (size_t i = 1; i < n; i++)
	{
		auto p = ConvertCoord(body[i]);
		gotoxy(p.X, p.Y);
		textbackground(COLORS::BLACK);
		textcolor(COLORS::WHITE);
		if (snake == _snake2) {
			textcolor(COLORS::LIGHTCYAN);
		}
		_putch('0');
	}
}

void UI::RenderFood(Food* food)
{
	auto c = ConvertCoord(food->GetLocation());
	gotoxy(c.X, c.Y);
	textcolor(COLORS::RED);
	_putch('*');
}

UI::UI(Snake* snake, Food* food,
	Snake* snake2 = nullptr, Food* food2 = nullptr,
	int boardHeight, int boardWidth) :
	BoardHeight(boardHeight), BoardWidth(boardWidth),
	BoardStart(COORD() = { (short)BoardStartX, (short)BoardStartY }),
	BoardEnd(COORD() = { (short)BoardStartX + (short)BoardWidth, (short)BoardStartY + (short)BoardHeight })
{
	_snake = snake;
	_food = food;
	_snake2 = snake2;
	_food2 = food2;
}

void UI::Render(int score, int score2)
{
	_setcursortype(_NOCURSOR);
	clrscr();
	gotoxy(1, 1);
	RenderBoard(score, score2);
	if (_snake != nullptr)
		RenderSnake(_snake);
	if (_snake2 != nullptr)
		RenderSnake(_snake2);
	RenderFood(_food);
	if (_food2 != nullptr)
		RenderFood(_food2);
	gotoxy(1, 1);
}

void UI::SnakeRemove(int snakeNum)
{
	snakeNum == 1 ? _snake = nullptr : _snake2 = nullptr;
}


UI::~UI()
{
}
