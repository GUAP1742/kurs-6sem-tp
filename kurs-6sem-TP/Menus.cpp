#include "Menus.h"

using namespace std;
using namespace sf;

int moves, timer, alert, active, from, num, win;
Stick* stick[3];
Disk* picked;

Clock clk;

#if MODE == 1

RenderWindow window(VideoMode(640, 360), "Hanoi tower");

void Rules()
{
	const int optnum = 18;

	Font font;
	font.loadFromFile("Bender.ttf");

	Text opt[optnum];

	opt[0].setString(L"Есть три пирамидки. В самом начале игры левая пирамидка запол-");
	opt[1].setString(L"нена дисками разных размеров. Правая и центральная пирамидки");
	opt[2].setString(L"пустые. Необходимо переместить все диски с левой на правую пи-");
	opt[3].setString(L"рамидку.");
	opt[4].setString(L"");
	opt[5].setString(L"При переносе учитывать ограничения:");
	opt[6].setString(L"<*> За раз переносится только один диск;");
	opt[7].setString(L"<*> Можно брать один из верхних кругов любой пирамидки и перено-");
	opt[8].setString(L"сить на любой из соседних стержней;");
	opt[9].setString(L"<*> Диск большего размера не может покрывать меньший.");
	opt[10].setString(L"");
	opt[11].setString(L"Управление осуществляется перемещением курсора и нажатием на");
	opt[12].setString(L"левую кнопку мыши.");
	opt[13].setString(L"");
	opt[14].setString(L"Постарайтесь пройти игру, выполнив как можно меньшее число пе-");
	opt[15].setString(L"ремещений за как можно меньшее время, чтобы попасть в таблицу");
	opt[16].setString(L"рекордов. Желаем удачи!");
	opt[17].setString(L"< Назад");

	for (int i = 0; i < optnum; ++i)
	{
		opt[i].setFont(font);
		opt[i].setFillColor(Color(0, 0, 85));

		if (i != 17)
		{
			opt[i].setCharacterSize(20);
			opt[i].move(10, 5 + 20 * i);
		}	
		else
		{
			opt[17].setCharacterSize(25);
			opt[17].move(500, 5 + 20 * 16);
		}
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (IntRect(500, 15 + 20 * 16, 240, 15).contains(Mouse::getPosition(window)))
					return;
			}
		}

		window.clear(Color::White);

		for (int i = 0; i < optnum; ++i)
		{
			if (IntRect(500, 15 + 20 * 16, 240, 15).contains(Mouse::getPosition(window)))
				opt[17].setFillColor(Color(252, 0, 85));
			else
				opt[17].setFillColor(Color(0, 0, 85));

			window.draw(opt[i]);
		}

		window.display();
	}
}

int MainMenu()
{
	Font font;
	font.loadFromFile("Bender.ttf");

	Text opt[4];

	opt[0].setString(L"<*> Новая игра");
	opt[1].setString(L"<*> Правила игры");
	opt[2].setString(L"<*> Рекорды");
	opt[3].setString(L"<*> Выход");

	for (int i = 0; i < 4; ++i)
	{
		opt[i].setFont(font);
		opt[i].setCharacterSize(50);
		opt[i].move(130, 60 + 50 * i);
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (IntRect(0, 75 + 50 * 0, 640, 40).contains(Mouse::getPosition(window)))
					return 0;

				if (IntRect(0, 75 + 50 * 1, 640, 40).contains(Mouse::getPosition(window)))
					Rules();
						
				if (IntRect(0, 75 + 50 * 2, 640, 40).contains(Mouse::getPosition(window)))
				{
					Initial(Mode());
					ScoresScreen();
				}

				if (IntRect(0, 75 + 50 * 3, 640, 40).contains(Mouse::getPosition(window)))
				{
					window.close();
					exit(0);
				}
			}
		}

		window.clear(Color::White);

		for (int i = 0; i < 4; ++i)
		{
			opt[i].setFillColor(Color(0, 0, 85));

			if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(window)))
				opt[i].setFillColor(Color(252, 0, 85));

			window.draw(opt[i]);
		}

		window.display();
	}

	return 1;
}

#endif

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
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}

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
		
		screenSpt.setScale(Vector2f(scale, scale));
		screenSpt.setPosition(0, 0);
		screenSpt.move(320 - 285 * scale, 180 - 60 * scale);

		window.clear(Color::White);
		window.draw(screenSpt);
		window.display();
	}

#endif
}

int Mode()
{
#if MODE == 0

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

#elif MODE == 1

	Font font;
	font.loadFromFile("Bender.ttf");

	Text opt[4];

	opt[0].setString(L"<3> диска");
	opt[1].setString(L"<4> диска");
	opt[2].setString(L"<5> дисков");
	opt[3].setString(L"<6> дисков");

	for (int i = 0; i < 4; ++i)
	{
		opt[i].setFont(font);
		opt[i].setCharacterSize(50);
		opt[i].move(130, 60 + 50 * i);
	}

	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				for (int i = 0; i < 4; ++i)
				{
					if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(window)))
						return i + 3;
				}
			}
		}

		window.clear(Color::White);

		for (int i = 0; i < 4; ++i)
		{
			opt[i].setFillColor(Color(0, 0, 85));

			if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(window)))
				opt[i].setFillColor(Color(252, 0, 85));

			window.draw(opt[i]);
		}

		window.display();
	}

	return 3;
#endif
}

void Initial(int n)
{
	clk.restart();

	alert = 0;
	active = 0;
	moves = 0;
	timer = 0;
	win = 0;
	num = n;
	picked = nullptr;

	stick[0] = new Stick(n);
	stick[1] = new Stick(n);
	stick[2] = new Stick(n);

	stick[0]->Fill(n);
}

#if MODE == 0

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

#endif

int Action(char& o)
{
	Menu menu;
	int ret = 1;
	int i = 0;

	Font font;
	Text opt[2];

	switch (o)
	{
#if MODE == 0

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
				if (from != active)
				{
					++moves;
					timer = clk.getElapsedTime().asSeconds();
				}
			}
			else alert = 1;
		}
		else return 0;
		break;
#endif

	case 8:

#if MODE == 0

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

#elif MODE == 1

		font.loadFromFile("Bender.ttf");

		opt[0].setString(L"<*> Выйти");
		opt[1].setString(L"<*> Продолжить игру");

		for (int i = 0; i < 2; ++i)
		{
			opt[i].setFont(font);
			opt[i].setCharacterSize(50);
			opt[i].move(100, 60 + 50 * i);
		}

		while (window.isOpen())
		{
			Event event;
			while (window.pollEvent(event))
			{
				if (event.type == Event::Closed)
					window.close();

				if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
				{
					for (int i = 0; i < 2; ++i)
					{
						if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(window)))
						{
							if (i == 0) o = 0;
							return 1;
						}
					}
				}
			}

			window.clear(Color::White);

			for (int i = 0; i < 2; ++i)
			{
				opt[i].setFillColor(Color(0, 0, 85));

				if (IntRect(0, 75 + 50 * i, 640, 40).contains(Mouse::getPosition(window)))
					opt[i].setFillColor(Color(252, 0, 85));

				window.draw(opt[i]);
			}

			window.display();
		}
#endif
	default:
		return 0;
	}

	if (stick[2]->Cnt() == (num - 1)) win = 1;
	return 1;
}

void GameScreen()
{
#if MODE == 0

	char o;
	
	while (1)
	{
		system("cls");
		cout << "Перемещений: " << moves << "  " << "Время: " << timer << endl;
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

#elif MODE == 1

	int m1 = 80,
		m2 = 140,
		m3 = 30;
	char o = 1;
	float sec3 = -4;

	Font font;
	font.loadFromFile("Bender.ttf");

///// TEXTS /////
	Text tmoves[2], ttime[2], talert[2], tpause;

	for (int i = 0; i < 2; ++i)
	{
		tmoves[i].setFont(font);
		ttime[i].setFont(font);
		talert[i].setFont(font);

		tmoves[i].setCharacterSize(30);
		ttime[i].setCharacterSize(30);

		tmoves[i].setFillColor(Color(0, 0, 85));
		ttime[i].setFillColor(Color(0, 0, 85));
		talert[i].setFillColor(Color(0, 0, 85));
	}
	talert[0].setCharacterSize(20);
	talert[1].setCharacterSize(40);

	tmoves[1].setStyle(Text::Bold);
	ttime[1].setStyle(Text::Bold);
	talert[0].setStyle(Text::Bold);
	talert[1].setStyle(Text::Bold);

	tmoves[0].setString(L"Перемещений:");
	ttime[0].setString(L"Время:");
	talert[0].setString(L"Нельзя ставить диски большего размера поверх меньших!");
	talert[1].setString(L"Победа!!!");

	tpause.setFont(font);
	tpause.setCharacterSize(30);
	tpause.setFillColor(Color(0, 0, 85));
	tpause.setString(L"Пауза >");

	tmoves[0].move(10, 10);
	tmoves[1].move(10 + 210, 10);
	ttime[0].move(10 + 210 + 70, 10);
	ttime[1].move(10 + 210 + 70 + 100, 10);
	talert[0].move(10, 50);
	talert[1].move(10, 50);
	tpause.move(500, 10);

///// RECTANGLES /////
	RectangleShape stver[3], sthor[3], sdisk[6];

	for (int i = 0; i < 3; ++i)
	{
		stver[i].setFillColor(Color(192, 192, 192));
		sthor[i].setFillColor(Color(160, 160, 160));

		stver[i].setSize(Vector2f(10, m2 - 10));
		sthor[i].setSize(Vector2f(m2, 10));

		stver[i].move(m1 + m2 * i + m3 * i + (m2 / 2) - 5, 310 - m2 + 10);
		sthor[i].move(m1 + m2 * i + m3 * i, 310);

		stver[i].setOutlineThickness(1);
		sthor[i].setOutlineThickness(1);
	}

	for (int i = 0; i < 6; ++i)
	{
		sdisk[i].setSize(Vector2f(20 * (i + 1), 20));
	}
	sdisk[0].setFillColor(Color(236, 0, 0));
	sdisk[1].setFillColor(Color(255, 132, 50));
	sdisk[2].setFillColor(Color(255, 216, 0));
	sdisk[3].setFillColor(Color(52, 213, 0));
	sdisk[4].setFillColor(Color(0, 95, 204));
	sdisk[5].setFillColor(Color(178, 0, 255));

///// GAME SCREEN /////
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				delete stick[0];
				delete stick[1];
				delete stick[2];
				window.close();
			}	

		///// CLICK ON STICKS /////
			for (int i = 0; i < 3; ++i)
			{
				if (IntRect(m1 + m2 * i + m3 * i, 310 - m2 - 50, m2, m2 + 50 + 30).contains(Mouse::getPosition(window)))
				{
					active = i;

					if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
					{
						if (picked)
						{
							if (stick[active]->Put(picked))
							{
								picked = nullptr;
								if (from != active)
								{
									++moves;
									timer = clk.getElapsedTime().asSeconds();
								}
							}
							else sec3 = clk.getElapsedTime().asSeconds();
						}
						else
						{
							picked = stick[active]->Pick();
							from = active;
						}
					}
				}
			}

		///// CLICK ON PAUSE /////
			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (IntRect(500, 15, 100, 25).contains(Mouse::getPosition(window)))
				{
					o = 8;
					Action(o);
				}
			}
		}

		window.clear(Color::White);

	///// TIMER AND MOVES /////
		timer = clk.getElapsedTime().asSeconds();

		tmoves[1].setString(to_string(moves));
		ttime[1].setString(to_string(timer / 60) + ':' + to_string((timer % 60) / 10) + to_string((timer % 60) % 10));

		for (int i = 0; i < 2; ++i)
		{
			window.draw(tmoves[i]);
			window.draw(ttime[i]);
		}

	///// WRONG PLACEMENT ALERT /////
		if ((clk.getElapsedTime().asSeconds() - sec3) <= 3)
		{
			cout << "\a";
			window.draw(talert[0]);
		}

	///// PAUSE BUTTON COLORING /////
		tpause.setFillColor(Color(0, 0, 85));
		if (IntRect(500, 15, 100, 25).contains(Mouse::getPosition(window)))
			tpause.setFillColor(Color(252, 0, 85));
		window.draw(tpause);

	///// STICKS OUTLINE COLORING /////
		for (int i = 0; i < 3; ++i)
		{
			stver[i].setOutlineColor(Color(0, 0, 0, 0));
			sthor[i].setOutlineColor(Color(0, 0, 0, 0));

			if (IntRect(m1 + m2 * active + m3 * active, 310 - m2 - 50, m2, m2 + 50 + 30).contains(Mouse::getPosition(window)))
			{
				stver[active].setOutlineColor(Color(252, 0, 85));
				sthor[active].setOutlineColor(Color(252, 0, 85));
			}
			
			window.draw(stver[i]);
			window.draw(sthor[i]);
		}

	///// DISKS DRAWING /////
		if (picked)
		{
			sdisk[picked->Size() - 1].setPosition(
				m1 + 10 * (5 - picked->Size() + 1) + 10 + (m2 + m3) * active,
				310 - 20 * (5 - 0 + 1) - 20 - 100);
		}

		for (int i = num - 1; i >= 0; --i)
		{
			for (int j = 0; j < 3; ++j)
			{
				if (stick[j]->Layer(i))
					sdisk[stick[j]->Layer(i) - 1].setPosition(
						m1 + 10 * (5 - stick[j]->Layer(i) + 1) + 10 + (m2 + m3) * j,
						310 - 20 * (i + 0) - 20);
			}

			window.draw(sdisk[i]);
		}

	///// WIN ALGORITHM /////
		if (win)
		{
			cout << "\a";
			sec3 = clk.getElapsedTime().asSeconds();
			window.draw(talert[1]);
			window.display();
			while ((clk.getElapsedTime().asSeconds() - sec3) <= 3);
			return;
		}

	///// DISPLAY ALL /////
		window.display();

	///// ADDITIONAL CONDITIONS /////
		if (stick[2]->Cnt() == (num - 1)) win = 1;
		if (!o) return;
	}

#endif
}

int ScoresScreen()
{
#if MODE == 0

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

#elif MODE == 1

///// STICKS DELETION /////
	delete stick[0];
	delete stick[1];
	delete stick[2];

///// NON-VISUAL VARIABLES /////
	ifstream fin;
	ofstream fout;
	string fname = "GScores" + to_string(num) + ".txt";
	string str[10], name[10];
	char uname[] = "AAAAA";
	int score[10], time[10];
	int i = 0, j, n;

	Font font;
	font.loadFromFile("Bender.ttf");

///// RECORDS SCREEN TEXTS /////
	Text tname[10], tdots[10],
		tscore[10], ttime[10], cont;

	for (int i = 0; i < 10; ++i)
	{
		tname[i].setFont(font);
		tdots[i].setFont(font);
		tscore[i].setFont(font);
		ttime[i].setFont(font);

		tname[i].setCharacterSize(30);
		tdots[i].setCharacterSize(30);
		tscore[i].setCharacterSize(30);
		ttime[i].setCharacterSize(30);

		tname[i].move(10, 10 + 30 * i);
		tdots[i].move(120, 0 + 30 * i);
		tscore[i].move(340, 10 + 30 * i);
		ttime[i].move(430, 10 + 30 * i);

		tname[i].setFillColor(Color(0, 0, 85));
		tdots[i].setFillColor(Color(0, 0, 85));
		tscore[i].setFillColor(Color(0, 0, 85));
		ttime[i].setFillColor(Color(0, 0, 85));
	}
	cont.setFont(font);
	cont.setCharacterSize(35);
	cont.move(270, 10 + 30 * 10);
	cont.setString(L"Продолжить >");

///// NAME SCREEN TEXTS /////
	Text tuname[9];

	for (int i = 0; i < 9; ++i)
	{
		tuname[i].setFont(font);
		tuname[i].setCharacterSize(50);
		if (i >= 1 && i <= 5)
		{
			tuname[i].move(130 + i * 50, 20 + 50);
		}	
		tuname[i].setFillColor(Color(0, 0, 85));
	}
	tuname[0].setString(L"Введите имя: (для переключения букв используйте колесо мыши)");
	tuname[0].setCharacterSize(20);
	tuname[0].move(10, 10);

	tuname[6].setString(L"v");

	tuname[7].setString(L"v");
	tuname[7].rotate(180);

	tuname[8].setString(L"Продолжить >");
	tuname[8].setCharacterSize(35);
	tuname[8].move(270, 10 + 30 * 10);

	fin.open(fname);
	if (!fin.fail())
	{
	///// READING THE EXISTING FILE /////
		while (!fin.eof() && i < 10)
		{
			name[i] = "     ";
			score[i] = 0;
			time[i] = 0;
			getline(fin, str[i], '\n');
			for (j = 0; str[i][j] != '\t'; ++j) {
				name[i][j] = str[i][j];
			}
			tname[i].setString(name[i]);
			tdots[i].setString(".........................................");
			for (++j; str[i][j] != '\t'; ++j) {
				score[i] *= 10;
				score[i] += str[i][j] - '0';
			}
			tscore[i].setString(to_string(score[i]));
			for (++j; str[i][j] != '\0'; ++j) {
				time[i] *= 10;
				time[i] += str[i][j] - '0';
			}
			ttime[i].setString(to_string(time[i] / 60) + ':' + to_string((time[i] % 60) / 10) + to_string((time[i] % 60) % 10));
			++i;
		}
		fin.close();

	///// IF THE GAME WAS FINISHED /////
		if (win)
		{
			if ((moves < score[9]) || ((moves == score[9]) && (timer <= time[9])))
			{
			///// NAME SCREEN /////
				n = 1;
				int ex = 0;
				while (window.isOpen() && !ex)
				{
					Event event;
					while (window.pollEvent(event))
					{
						if (event.type == Event::Closed)
							window.close();

						if (event.type == Event::MouseWheelMoved)
						{
							if (IntRect(130 + n * 50, 20 + 50 - 10, 50 - 20, 50 + 15).contains(Mouse::getPosition(window)))
							{
								if (event.mouseWheel.delta > 0)
								{
									if (uname[n - 1] == '0') break;
									if (uname[n - 1] == 'A') uname[n - 1] = '9';
									else --uname[n - 1];
								}
								else if (event.mouseWheel.delta < 0)
								{
									if (uname[n - 1] == 'Z') break;
									if (uname[n - 1] == '9') uname[n - 1] = 'A';
									else ++uname[n - 1];
								}
							}
						}

						if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
						{
							if (IntRect(270, 20 + 30 * 10, 220, 30).contains(Mouse::getPosition(window)))
								ex = 1;
						}
					}

					window.clear(Color::White);

					for (int i = 0; i < 9; ++i)
					{
						tuname[8].setFillColor(Color(0, 0, 85));

						for (int j = 1; j <= 5; ++j)
						{
							tuname[j].setString(uname[j - 1]);

							tuname[j].setFillColor(Color(0, 0, 85));
							tuname[6].setFillColor(Color(0, 0, 85));
							tuname[7].setFillColor(Color(0, 0, 85));

							if (IntRect(130 + j * 50, 20 + 50 - 10, 50 - 20, 50 + 15).contains(Mouse::getPosition(window)))
							{
								tuname[j].setFillColor(Color(252, 0, 85));
								tuname[6].setFillColor(Color(252, 0, 85));
								tuname[7].setFillColor(Color(252, 0, 85));
								n = j;
								break;
							}
						}

						tuname[6].setPosition(132 + n * 50, 20 + 5);
						tuname[7].setPosition(132 + n * 50 + 25, 20 + 50 + 50 * 2 + 8);

						if (IntRect(270, 20 + 30 * 10, 220, 30).contains(Mouse::getPosition(window)))
							tuname[8].setFillColor(Color(252, 0, 85));

						if (i != 6 && i != 7)
							window.draw(tuname[i]);
						else if((int)(clk.getElapsedTime().asSeconds() * 100) % 100 < 25 ||
							((int)(clk.getElapsedTime().asSeconds() * 100) % 100 >= 50 &&
							(int)(clk.getElapsedTime().asSeconds() * 100) % 100 < 75))
							window.draw(tuname[i]);
					}

					window.display();
				}

				if (ex)
				{
				///// FINDING NEW RECORD POSITION /////
					for (i = 0; i < 10; ++i)
					{
						if ((moves < score[i]) || ((moves == score[i]) && (timer <= time[i])))
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
					str[n] += "\t" + to_string(moves) + "\t" + to_string(timer);

				///// SETUPS FOR RECORDS SCREEN /////
					for (i = 0; i < 10; ++i)
					{
						score[i] = 0;
						time[i] = 0;
						for (j = 0; str[i][j] != '\t'; ++j) {
							name[i][j] = str[i][j];
						}
						tname[i].setString(name[i]);
						tdots[i].setString(".........................................");
						for (++j; str[i][j] != '\t'; ++j) {
							score[i] *= 10;
							score[i] += str[i][j] - '0';
						}
						tscore[i].setString(to_string(score[i]));
						for (++j; str[i][j] != '\0'; ++j) {
							time[i] *= 10;
							time[i] += str[i][j] - '0';
						}
						ttime[i].setString(to_string(time[i] / 60) + ':' + to_string((time[i] % 60) / 10) + to_string((time[i] % 60) % 10));
					}

				///// OVERWRITING THE FILE /////
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
		}
	}
	else cout << "Ошибка чтения из файла рекордов!" << endl;

///// RECORDS SCREEN /////
	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();

			if (event.type == Event::MouseButtonReleased && event.mouseButton.button == Mouse::Left)
			{
				if (IntRect(270, 20 + 30 * 10, 220, 30).contains(Mouse::getPosition(window)))
					return 1;
			}
		}

		window.clear(Color::White);

		for (int i = 0; i < 10; ++i)
		{
			cont.setFillColor(Color(0, 0, 85));

			if (IntRect(270, 20 + 30 * 10, 220, 30).contains(Mouse::getPosition(window)))
				cont.setFillColor(Color(252, 0, 85));

			window.draw(tname[i]);
			window.draw(tdots[i]);
			window.draw(tscore[i]);
			window.draw(ttime[i]);
		}
		window.draw(cont);

		window.display();
	}
	return 1;
#endif
}

int Game(int n)
{
	Initial(n);
	GameScreen();
	return ScoresScreen();
}