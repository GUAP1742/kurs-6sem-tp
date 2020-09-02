#pragma once
#include <SFML/Graphics.hpp>
#include "Stick.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>

#define MODE 1

#include "Menu.h"





using namespace std;

#if MODE == 1

void Rules();
int MainMenu();

#endif

void Start();
int Mode();
void Initial(int n);
string PrintActive();
string PrintLayer(int i);
int Action(char& o);
void GameScreen();
int ScoresScreen();
int Game(int n);