#include "Stick.h"

Stick::Stick()
{
	n = 0;
	k = -1;
	layer = nullptr;
}

Stick::Stick(int n)
{
	this->n = n;
	k = -1;
	layer = new Disk*[n];
	for (int i = 0; i < n; ++i)
	{
		layer[i] = nullptr;
	}
}

Stick::~Stick()
{
	for (int i = 0; i < n; ++i)
		delete layer[i];
	delete[] layer;
}

int Stick::Cnt()
{
	return k;
}

int Stick::Layer(int i)
{
	if (i > k) return 0;
	return layer[i]->Size();
}

int Stick::Put(Disk* d)
{
	if (k >= 0 && layer[k]->Size() < d->Size()) return 0;
	++k;
	layer[k] = d;
	return 1;
}

Disk* Stick::Pick()
{
	if (k == -1) return nullptr;
	Disk* tmp = layer[k];
	layer[k] = nullptr;
	--k;
	return tmp;
}

void Stick::Fill(int k)
{
	for (int i = 0; i < k; ++i)
	{
		Disk* d = new Disk(k - i);
		Put(d);
	}
}