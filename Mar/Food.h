#pragma once
#include<Windows.h>
#include<ctime>

using namespace std;

class Snake;

class Food
{
	const int d;
	COORD Location;
public:
	COORD GetLocation();
	void PutNew();

	Food(int);
	~Food();
};

