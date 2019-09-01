#pragma once
#include "conio21\conio2.h"
#include <cctype>

class Keyboard
{
public:
	Keyboard();
	~Keyboard();

	enum class Key
	{
		_NoKey = '\0',

		A = 'A',
		D = 'D',
		S = 'S',
		W = 'W',

		J = 'J',
		L = 'L',
		K = 'K',
		I = 'I'
	};

	Key IsKeyPressed() {
		if(!_kbhit())
			return Key::_NoKey;
		
		char inChar = _getch();
		inChar = std::toupper(inChar);
		return (Key)inChar;
	}
};

