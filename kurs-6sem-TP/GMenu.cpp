#include "GMenu.h"

GMenu::GMenu()
{
	window = nullptr;
	num = 0;
	ret = 0;
	opt = nullptr;
}

GMenu::GMenu(RenderWindow* window, int num)
{
	this->window = window;
	this->num = num;
	ret = 0;
	opt = new Text[num];

	Font font;
	font.loadFromFile("Bender.ttf");

	for (int i = 0; i < num; ++i)
	{
		opt[i].setFont(font);
		opt[i].setCharacterSize(50);
		opt[i].move(200, 60 + 50 * i);
	}
}

GMenu::~GMenu() 
{
	if (num == 1) 
		delete opt;
	else if (num > 1) 
		delete[] opt;
}

void GMenu::Check()
{
	Event event;
	while (window->pollEvent(event))
	{
		if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
		{
			for (int i = 0; i < num; ++i)
			{
				if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(*window)))
					ret = i;
			}
		}
	}

	for (int i = 0; i < num; ++i)
	{
		opt[i].setFillColor(Color(0, 0, 85));

		if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(*window)))
			opt[i].setFillColor(Color(252, 0, 85));

		//window->draw(opt[i]);
	}
}

int GMenu::Return()
{
	return ret;
}