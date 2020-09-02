#pragma once
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

class GMenu
{
	RenderWindow* window;
	int num;
	int ret;

public:
	Text* opt;

	GMenu();
	GMenu(RenderWindow* window, int num);
	~GMenu();

	void Check();
	int Return();
};