#include "Menus.h"

using namespace std;

int moves, alert, active, from, num, win;
Stick* stick[3];
Disk* picked;

void Start()
{
	cout << "Добро пожаловать в игру \"Ханойская башня\"!" << endl;
	Sleep(3000);
}

int Mode()
{
	int n = 3, ex = 0;
	string cursor[4] = { "> ", "  ", "  ", "  " };

	while (!ex)
	{
		system("cls");
		cout << "Выберите режим игры:" << endl << endl;
		cout << cursor[0] << "<3> диска" << endl;
		cout << cursor[1] << "<4> диска" << endl;
		cout << cursor[2] << "<5> дисков" << endl;
		cout << cursor[3] << "<6> дисков" << endl;

		switch (_getch())
		{
		case 72:
			if (n != 3) --n;
			cursor[n - 2] = "  ";
			cursor[n - 3] = "> ";
			break;
		case 80:
			if (n != 6) ++n;
			cursor[n - 4] = "  ";
			cursor[n - 3] = "> ";
			break;
		case 13:
			return n;
		default:
			break;
		}
	}
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
	string cursor[2] = { "> ", "  " };
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
		while (o)
		{
			system("cls");
			cout << "Выйти?" << endl << endl;
			cout << cursor[0] << "<0> Нет" << endl;
			cout << cursor[1] << "<1> Да" << endl;
			switch (_getch())
			{
			case 72:
				if (i) --i;
				cursor[0] = "> ";
				cursor[1] = "  ";
				break;
			case 80:
				if (!i) ++i;
				cursor[0] = "  ";
				cursor[1] = "> ";
				break;
			case 13:
				if (i) o = 0;
				else return 1;
				break;
			default:
				break;
			}
		}
		break;
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
			while (!fin.eof())
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

	string cursor[2] = { "  ", "> " };
	int c = 1;

	while (1)
	{
		system("cls");
		cout << cursor[1] << "<1> Новая игра" << endl;
		cout << cursor[0] << "<0> Выход" << endl;
		switch (_getch())
		{
		case 72:
			if (!c) ++c;
			cursor[1] = "> ";
			cursor[0] = "  ";
			break;
		case 80:
			if (c) --c;
			cursor[1] = "  ";
			cursor[0] = "> ";
			break;
		case 13:
			return c;
		default:
			break;
		}
	}
}

int Game(int n)
{
	Initial(n);
	GameScreen();
	return ScoresScreen();
}