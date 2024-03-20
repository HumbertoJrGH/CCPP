#include "celula.h"

Celula::Celula(int x)
{
	this->next = this->prev = nullptr;
	this->val = x;
}

int Celula::getValue()
{
	return this->val;
}