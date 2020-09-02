#include "Menus.h"

using namespace std;
using namespace sf;

int moves, alert, active, from, num, win;
Stick* stick[3];
Disk* picked;

RenderWindow window(VideoMode(640, 360), "Hanoi tower");
Clock clk;

void Start()
{
#if MODE == 0

	cout << "Добро пожаловать в игру \"Ханойская башня\"!" << endl;
	Sleep(3000);

#elif MODE == 1

	float scale = 0.5f, alpha = 0;

	Texture screenTxr;
	screenTxr.loadFromFile("startscreen.png");
	screenTxr.setSmooth(true);

	Sprite screenSpt(screenTxr);
	screenSpt.setScale(Vector2f(scale, scale));
	screenSpt.move(320 - 285 * scale, 180 - 60 * scale);

	float time = 0, timer = 0, i = 0;
	while (window.isOpen() && timer <= 3000)
	{
		time += clk.getElapsedTime().asMicroseconds();
		clk.restart();
		if (time >= 1000)
		{
			time = 0;
			timer++;
			scale += 0.0002f;

			if (timer <= 1000)
			{
				alpha += 0.255f;
				screenSpt.setColor(Color(255, 255, 255, alpha));
			}
			else if (timer > 2000)
			{
				alpha -= 0.255f;
				screenSpt.setColor(Color(255, 255, 255, alpha));
			}
		}

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
		
		screenSpt.setScale(Vector2f(scale, scale));
		screenSpt.setPosition(0, 0);
		screenSpt.move(320 - 285 * scale, 180 - 60 * scale);

		window.clear(Color::White);
		window.draw(screenSpt);
		window.display();
	}
	system("pause");

#endif
}

int Mode()
{
	Menu menu;
	menu.AddOption("<3> диска", 3);
	menu.AddOption("<4> диска", 4);
	menu.AddOption("<5> дисков", 5);
	menu.AddOption("<6> дисков", 6);

	int ret = 1;
	do
	{
		if (ret != 2)
		{
			system("cls");
			menu.Display();
		}
	} while (ret = menu.ReadInput());

	return menu.Return();
}

void Initial(int n)
{
	alert = 0;
	active = 0;
	moves = 0;
	win = 0;
	num = n;
	picked = nullptr;

	stick[0] = new Stick(n);
	stick[1] = new Stick(n);
	stick[2] = new Stick(n);

	stick[0]->Fill(n);
}

string PrintActive()
{
	string s[3];
	string l;
	int size;

	if (picked)
	{
		for (int j = 0; j < 3; ++j)
		{
			l = "";
			size = 2 * picked->Size();
			if (!size) size = 2;
			for (int n = 0; n < (12 - size) / 2; ++n)
			{
				l += " ";
			}
			for (int n = 0; n < (size - 1); ++n)
			{
				if (j == active) l += "*";
				else l += " ";
			}
			for (int n = 0; n < (12 - size) / 2; ++n)
			{
				l += " ";
			}
			s[j] = l;
		}
	}
	else
	{
		for (int j = 0; j < 3; ++j)
		{
			if (j == active)
				s[j] += "    *V*    ";
			else
				s[j] += "           ";
		}
	}

	return s[0] + "   " + s[1] + "   " + s[2];
}

string PrintLayer(int i)
{
	string s[3];
	string l;
	int size;

	for (int j = 0; j < 3; ++j)
	{
		l = "";
		size = 2 * stick[j]->Layer(i);
		if (!size) size = 2;

		for (int n = 0; n < (12 - size) / 2; ++n)
		{
			l += " ";
		}
		for (int n = 0; n < (size - 1); ++n)
		{
			if (stick[j]->Layer(i)) l += "*";
			else l += "|";
		}
		for (int n = 0; n < (12 - size) / 2; ++n)
		{
			l += " ";
		}
		s[j] = l;
	}
	return s[0] + "   " + s[1] + "   " + s[2];
}

int Action(char& o)
{
	Menu menu;
	int ret = 1;
	int i = 0;

	switch (o)
	{
	case 75:
		if (active != 0) --active;
		else return 0;
		break;

	case 77:
		if (active != 2) ++active;
		else return 0;
		break;

	case 72:
		if (!picked) picked = stick[active]->Pick();
		else return 0;
		from = active;
		if (!picked) return 0;
		break;

	case 80:
		if (picked)
		{
			if (stick[active]->Put(picked))
			{
				picked = nullptr;
				if (from != active) ++moves;
			}
			else alert = 1;
		}
		else return 0;
		break;

	case 8:
		menu.AddOption("<0> Нет", 0);
		menu.AddOption("<1> Да", 1);
		do
		{
			if (ret != 2)
			{
				system("cls");
				cout << "Выйти?" << endl << endl;
				menu.Display();
			}
		} while (ret = menu.ReadInput());

		if (menu.Return() == 1) o = 0;
		return 1;

	default:
		return 0;
	}

	if (stick[2]->Cnt() == (num - 1)) win = 1;
	return 1;
}

void GameScreen()
{
	char o;
	
	while (1)
	{
		system("cls");
		cout << "Перемещений: " << moves << endl;
		if (alert) cout << "\aНельзя ставить большие диски поверх меньших!" << endl;
		else if (win)
		{
			cout << "\aПобеда!!!" << endl;
		}
		else
			cout << endl;
		cout << endl;
		cout << PrintActive() << endl;
		cout << endl;
		cout << "     |             |             |     " << endl;
		for (int i = num - 1; i >= 0; --i)
			cout << PrintLayer(i) << endl;
		cout << "|/\\/\\/\\/\\/|   |/\\/\\/\\/\\/|   |/\\/\\/\\/\\/|";
		alert = 0;
		if (win)
		{
			Sleep(3000);
			return;
		}

		while (!Action(o = _getch()));

		if (!o) return;
	}
}

int ScoresScreen()
{
	ifstream fin;
	ofstream fout;
	string fname = "Scores" + to_string(num) + ".txt";
	string str[10], name[10];
	char uname[] = "AAAAA";
	int score[10];
	int i = 0, j, n;

	system("cls");

	if (win)
	{
		fin.open(fname);
		if (!fin.fail())
		{
			while (!fin.eof() && i < 10)
			{
				name[i] = "     ";
				score[i] = 0;
				getline(fin, str[i], '\n');
				for (j = 0; str[i][j] != '\t'; ++j) {
					name[i][j] = str[i][j];
					cout << name[i][j];
				}
				cout << "....................";
				for (++j; str[i][j] != '\0'; ++j) {
					score[i] *= 10;
					score[i] += str[i][j] - '0';
				}
				cout << score[i];
				++i;
				cout << endl;
			}
			fin.close();

			if (moves > score[9])
			{
				cout << endl << "Ваш результат: " << moves << endl;
				cout << "Пробуйте ещё раз, чтобы попасть в десятку лучших!" << endl << endl;
			}
			else
			{
				i = 0;
				int ex = 0;
				while (!ex)
				{
					system("cls");
					cout << "Введите имя:" << endl << endl;
					for (j = 0; j < i; ++j)
						cout << " ";
					cout << "v" << endl;
					for (j = 0; j < 5; ++j)
						cout << uname[j];

					switch (_getch())
					{
					case 72:
						if (uname[i] == '0') break;
						if (uname[i] == 'A') uname[i] = '9';
						else --uname[i];
						break;

					case 80:
						if (uname[i] == 'Z') break;
						if (uname[i] == '9') uname[i] = 'A';
						else ++uname[i];
						break;

					case 75:
						if (i > 0) --i;
						break;

					case 77:
						if (i < 5) ++i;
						break;

					case 13:
						ex = 1;
						break;

					default:
						break;
					}
				}

				for (i = 0; i < 10; ++i)
				{
					if (moves <= score[i])
					{
						n = i;
						break;
					}
				}

				for (i = 9; i >= n; --i)
				{
					if (!i) break;
					str[i] = str[i - 1];
				}
				str[n] = uname;
				str[n] += "\t" + to_string(moves);

				system("cls");
				for (i = 0; i < 10; ++i)
				{
					for (j = 0; str[i][j] != '\t'; ++j)
						cout << str[i][j];
					cout << "....................";
					for (++j ; str[i][j] != '\0'; ++j)
						cout << str[i][j];
					cout << endl;
				}

				fout.open(fname);
				if (!fout.fail())
				{
					for (i = 0; i < 10; ++i)
					{
						fout << str[i] << endl;
					}
					fout.close();
				}
				else cout << "Ошибка записи в файл рекордов!" << endl;
			}
		}
		else cout << "Ошибка чтения из файла рекордов!" << endl;

		cout << endl;
		system("pause");
	}

	//fout.open(fname);

	//cout << "Таблица рекордов:" << endl << endl;
	//fin.open(fname);
	//if (!fin.fail())
	//{
	//	while (!fin.eof())
	//	{
	//		int i;
	//		getline(fin, str, '\n');
	//		for (i = 0; str[i] != '\t'; ++i)
	//			cout << str[i];
	//		cout << "....................";
	//		for (++i ; str[i] != '\0'; ++i)
	//			cout << str[i];
	//		cout << endl;
	//	}
	//	fin.close();
	//}
	//else cout << "Ошибка открытия файла рекордов!" << endl;

	delete stick[0];
	delete stick[1];
	delete stick[2];

	Menu menu;
	menu.AddOption("<1> Новая игра", 1);
	menu.AddOption("<0> Выход", 0);

	int ret = 1;
	do
	{
		if (ret != 2)
		{
			system("cls");
			menu.Display();
		}
	} while (ret = menu.ReadInput());

	return menu.Return();
}

int Game(int n)
{
	Initial(n);
	GameScreen();
	return ScoresScreen();
}