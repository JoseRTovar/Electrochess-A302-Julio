#pragma once
#include "Pieza.h"

class Alfil : public Pieza
{
public:
	Alfil(color_t color) :Pieza(color, ALFIL) {}
	virtual void dibuja();
	virtual bool validmove(int fo, int co, int fd, int cd);
};