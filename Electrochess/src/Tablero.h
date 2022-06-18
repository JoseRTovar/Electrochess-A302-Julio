#pragma once
#include "Pieza.h"
#include "Casilla.h"
#include "Rey.h"



class Tablero
{
public:
	static const int N_COL = 8;
	static const int N_FIL = 8;
	Casilla** casilla;
	float x_ojo;
	float y_ojo;
	float z_ojo;
	Rey ReyB;
	Rey ReyN;
public:
	void tecla(unsigned char key);
	void inicializa();
	void rotarOjo();
	void mueve();
	void dibuja();
};
