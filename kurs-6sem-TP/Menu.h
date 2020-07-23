#pragma once
#include <iostream>
#include <string>
#include <conio.h>

using namespace std;

class Menu
{
	string cursor;
	string* opt;
	int* ret;
	int num;
	int active;

public:
	Menu();
	Menu(string cursor);
	~Menu();

	void SetCursor(string cursor);
	void AddOption(string opt, int ret);
	void Display();
	int ReadInput();
	int Return();
};
