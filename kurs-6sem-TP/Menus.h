#pragma once
#include "Stick.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <fstream>
#include <string>

using namespace std;

void Start();
int Mode();
void Initial(int n);
string PrintActive();
string PrintLayer(int i);
int Action(char& o);
void GameScreen();
int ScoresScreen();
int Game(int n);