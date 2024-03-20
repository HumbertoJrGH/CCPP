#ifndef CELULA_H
#define CELULA_H

class Celula
{
private:
	int val;

public:
	Celula *next;
	Celula *prev;
	Celula(int x);
	int getValue();
};

#endif