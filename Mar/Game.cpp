#include "Game.h"

void Game::Run()
{
	int counter = 0;
	Direction sd1 = Direction::Right, sd2 = Direction::Right;
	while (true)
	{
		Keyboard::Key pressedKey = _keyboard->IsKeyPressed();
		if (pressedKey != Keyboard::Key::_NoKey) {
			switch (pressedKey)
			{
			case Keyboard::Key::A:
				if (_snake != nullptr)
					if (!IsOpposite(Direction::Left, _snake->GetDirection()))
						sd1 = (Direction::Left);
				break;
			case Keyboard::Key::D:
				if (_snake != nullptr)
					if (!IsOpposite(Direction::Right, _snake->GetDirection()))
						sd1 = (Direction::Right);
				break;
			case Keyboard::Key::S:
				if (_snake != nullptr)
					if (!IsOpposite(Direction::Down, _snake->GetDirection()))
						sd1 = (Direction::Down);
				break;
			case Keyboard::Key::W:
				if (_snake != nullptr)
					if (!IsOpposite(Direction::Up, _snake->GetDirection()))
						sd1 = (Direction::Up);
				break;
			case Keyboard::Key::J:
				if (_snake2 != nullptr)
					if (!IsOpposite(Direction::Left, _snake2->GetDirection()))
						sd2 = (Direction::Left);
				break;
			case Keyboard::Key::L:
				if (_snake2 != nullptr)
					if (!IsOpposite(Direction::Right, _snake2->GetDirection()))
						sd2 = (Direction::Right);
				break;
			case Keyboard::Key::K:
				if (_snake2 != nullptr)
					if (!IsOpposite(Direction::Down, _snake2->GetDirection()))
						sd2 = (Direction::Down);
				break;
			case Keyboard::Key::I:
				if (_snake2 != nullptr)
					if (!IsOpposite(Direction::Up, _snake2->GetDirection()))
						sd2 = (Direction::Up);
				break;
			default:
				break;
			}
		}

		if (counter == 0) {
			if (_snake != nullptr)
				this->_snake->SetDirection(sd1);
			if (_snake2 != nullptr)
				this->_snake2->SetDirection(sd2);
			size_t s1 = -1, s2 = -1;
			if (_snake != nullptr)
				_snake->GetBody(s1);
			if (_snake2 != nullptr)
				_snake2->GetBody(s2);
			SnakeMoved();
			_ui->Render(s1 - 3, s2 - 3);
		}
		counter = ++counter % 5;
		delay(20);
	}
}

void Game::SnakeMoved() {
	Snake * s[2] = { _snake, _snake2 };
	for (int i = 0; i < 2; i++)
	{
		if (s[i] == nullptr) continue;
		auto nextPlace = s[i]->GetNextPlace();
		auto eaten = false;
		if (nextPlace == _food->GetLocation()) {
			_food->PutNew();
			_food->PutNew();
			eaten = true;
		}
		if (_food2 != nullptr)
		{
			if (nextPlace == _food2->GetLocation()) {
				_food2->PutNew();
				_food2->PutNew();
				eaten = true;
			}
		}

		if (nextPlace.X == -1 || nextPlace.X == 41 ||
			nextPlace.Y == 0 || nextPlace.Y == 41) {
			DHit(i + 1, false);
			return;
		}

		size_t n;
		auto body = s[i]->GetBody(n);
		for (size_t j = 0; j < n; j++)
		{
			if (nextPlace == body[j]) {
				DHit(i + 1, false);
				return;
			}
		}
		if (s[(i + 1) % 2] != nullptr) {
			size_t n;
			auto body = s[(i + 1) % 2]->GetBody(n);
			for (size_t j = 0; j < n; j++)
			{
				if (nextPlace == body[j]) {
					DHit(i + 1, true);
					return;
				}
			}
		}

		s[i]->Move(eaten);
	}

}

void Game::Hit()
{
	clrscr();
	gotoxy(1, 1);
	if (_n == 1) {
		_cputs("Game Over\nYour score is ");
		size_t n;
		this->_snake->GetBody(n);
		_cputs(to_string(n - 3).c_str());
		_cputs("\n\n");
	}
	else
	{
		_cputs("Game Over\n");
		size_t s1;
		size_t s2;
		this->_snake->GetBody(s1);
		this->_snake2->GetBody(s2);
		if (s1 == s2) {
			cout << "Drow \n\n";
			system("pause");
			exit(0);
		}
		cout << "Player" << ((s1 > s2) ? "player1" : "player2") << "is winner \n";
		cout << "Player1 score: " << s1 << std::endl;
		cout << "Player2 score: " << s2 << std::endl << std::endl;
	}
	system("pause");
	exit(0);
}

void Game::DHit(int snakeNum, bool HitOther)
{
	size_t n1, n2;
	if (snakeNum == 1) {
		_snake->GetBody(n1); last1 = n1 - 3;
		delete _snake;
		_snake = nullptr;
	}
	else
	{
		_snake2->GetBody(n2); last2 = n2 - 3;
		delete _snake2;
		_snake2 = nullptr;
	}
	_ui->SnakeRemove(snakeNum);

	if (_snake == _snake2 && _snake2 == nullptr) {
		clrscr();
		cout << "Player" << snakeNum << " is winner\n";
		cout << "Player1 score : " << last1 << endl;
		cout << "Player2 score : " << last2 << endl;
		cout << endl;
		system("pause");
		exit(0);
	}
	if (HitOther) {
		if (snakeNum == 1) {
			last1 -= 3;
			DHit(2, false);
		}
		else
		{
			last2 -= 3;
			DHit(1, false);
		}
	}
}

Game::Game(int n = 1)
{
	this->_food = new Food(40);
	this->_food2 = nullptr;
	this->_keyboard = new Keyboard();
	this->_snake = new Snake();
	this->_snake2 = nullptr;

	_n = n;

	if (n == 2) {
		this->_food2 = new Food(40);
		this->_snake2 = new Snake();

		_snake2->Move();
		_snake2->Move();
		_snake2->Move();
		_snake2->Move();
		_snake2->Move();
	}

	this->_ui = new UI(_snake, _food, _snake2, _food2, 40, 40);

	this->_food->PutNew();
	if (_food2 != nullptr)
		_food2->PutNew();
	srand((int)time(0));
}

Game::~Game()
{
	delete _food;
	if (_food2 != nullptr)
		delete _food2;
	delete _keyboard;
	delete _snake;
	if (_snake2 != nullptr)
		delete _snake2;
	delete _ui;
}

int main() {
	std::cout << "how many players this game have? ";
	int n = 0;
	std::cin >> n;

	Game game(n);

	game.Run();

	system("pause");
	return 0;
}

bool operator==(COORD a, COORD b)
{
	return a.X == b.X && a.Y == b.Y;
}
