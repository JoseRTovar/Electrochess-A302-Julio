#pragma once
#include "Pieza.h"

class Torre : public Pieza
{
public:
	Torre(color_t color) :Pieza(color, TORRE) {}
	virtual void dibuja();
	virtual bool validmove(int fo, int co, int fd, int cd);
};