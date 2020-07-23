#include "Menu.h"

Menu::Menu()
{
	cursor = "> ";
	opt = nullptr;
	ret = nullptr;
	num = 0;
	active = 0;
}

Menu::Menu(string cursor)
{
	this->cursor = cursor;
	opt = nullptr;
	ret = nullptr;
	num = 0;
	active = 0;
}

Menu::~Menu()
{
	delete[] opt;
}

void Menu::SetCursor(string cursor)
{
	this->cursor = cursor;
}

void Menu::AddOption(string opt, int ret)
{
	if (!num)
	{
		this->opt = new string;
		this->ret = new int;

		this->opt[0] = opt;
		this->ret[0] = ret;

		++num;
	}
	else
	{
		string* opt_tmp;
		int* ret_tmp;

		opt_tmp = new string[num + 1];
		ret_tmp = new int[num + 1];

		for (int i = 0; i < num; ++i)
		{
			opt_tmp[i] = this->opt[i];
			ret_tmp[i] = this->ret[i];
		}
		opt_tmp[num] = opt;
		ret_tmp[num] = ret;

		delete[] this->opt;
		delete[] this->ret;
		this->opt = opt_tmp;
		this->ret = ret_tmp;

		++num;
	}
}

void Menu::Display()
{
	for (int i = 0; i < num; ++i)
	{
		if (i == active) cout << cursor;
		cout << opt[i] << endl;
	}
}

int Menu::ReadInput()
{
	switch (_getch())
	{
	case 72:
		if (active) --active;
		return 1;
	case 80:
		if (active < num - 1) ++active;
		return 1;
	case 13:
		return 0;
	default:
		return 1;
	}
}

int Menu::Return()
{
	return ret[active];
}