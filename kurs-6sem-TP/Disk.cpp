#include "Disk.h"

Disk::Disk()
{
	size = 0;
}

Disk::Disk(int n)
{
	size = n;
}

Disk::~Disk()
{}

int Disk::Size()
{
	return size;
}