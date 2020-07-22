#pragma once
#include "Disk.h"

class Stick
{
	int n;
	int k;
	Disk** layer;
	
public:
	Stick();
	Stick(int n);
	~Stick();

	int Cnt();
	int Layer(int i);
	int Put(Disk* d);
	Disk* Pick();
	void Fill(int n);
};
