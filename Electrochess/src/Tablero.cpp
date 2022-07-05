#include "Tablero.h"
#include "Juego.h"

Tablero::Tablero()
{
	for (int fila = 0; fila < N_FILAS; fila++)
	{
		for (int columna = 0; columna < N_COLUMNAS; columna++)
		{
			tab[fila][columna] = nullptr;
		}
	}

	tab[0][4] = new Rey(Pieza::BLANCA);
	tab[7][4] = new Rey(Pieza::NEGRA);
	tab[0][0] = new Torre(Pieza::BLANCA);
	tab[0][7] = new Torre(Pieza::BLANCA);
	tab[7][0] = new Torre(Pieza::NEGRA);
	tab[7][7] = new Torre(Pieza::NEGRA);
	tab[0][2] = new Alfil(Pieza::BLANCA);
	tab[0][5] = new Alfil(Pieza::BLANCA);
	tab[7][2] = new Alfil(Pieza::NEGRA);
	tab[7][5] = new Alfil(Pieza::NEGRA);
	tab[0][3] = new Reina(Pieza::BLANCA);
	tab[7][3] = new Reina(Pieza::NEGRA);
	tab[0][1] = new Caballo(Pieza::BLANCA);
	tab[0][6] = new Caballo(Pieza::BLANCA);
	tab[7][1] = new Caballo(Pieza::NEGRA);
	tab[7][6] = new Caballo(Pieza::NEGRA);
	for (int i = 0; i < 8; i++)
	{
		tab[1][i] = new Peon(Pieza::BLANCA);
		tab[6][i] = new Peon(Pieza::NEGRA);
	}

	for (int i = 0; i < 30; i++)
	{
		Comidas[i] = nullptr;
	}
}

void Tablero::cambiarEstado(Coordenadas origen, Coordenadas destino)
{
	if (tab[destino.fila][destino.columna] != nullptr)
	{
		Comidas[SizeComidas++] = tab[destino.fila][destino.columna];
		playMusica("Take.mp3");
		cout << "Pieza comida " << endl;
	}
	else playMusica("Move.mp3");

	tab[destino.fila][destino.columna] = tab[origen.fila][origen.columna];
	tab[origen.fila][origen.columna] = nullptr;

}

void Tablero::dibuja(Juego& juego)
{
	//Dibuja de un color verde las casillas a las que es posible mover la pieza seleccionada
	for (int i = 0; i < juego.getLegalMoves(); i++)
	{
		if ((juego[i]->fila + juego[i]->columna) % 2 == 0)  glColor3ub(50, 150, 50);
		else glColor3ub(100, 200, 100);
		glBegin(GL_POLYGON);
		glVertex3d(juego[i]->columna, juego[i]->fila, 0.0);
		glVertex3d(juego[i]->columna + 1.0, juego[i]->fila, 0.0);
		glVertex3d(juego[i]->columna + 1.0, juego[i]->fila + 1.0, 0.0);
		glVertex3d(juego[i]->columna, juego[i]->fila + 1.0, 0.0);
		glEnd();
		glEnable(GL_LIGHTING);
	}

	//Dibuja el tablero por completo
	for (int fila = 0; fila < N_FILAS; fila++)
	{
		for (int columna = 0; columna < N_COLUMNAS; columna++)
		{
			glDisable(GL_LIGHTING);
			if ((fila + columna) % 2 == 0) glColor3ub(100, 100, 100);
			else glColor3ub(255, 255, 255);
			glBegin(GL_POLYGON);
			glVertex3d(columna, fila, 0.0);
			glVertex3d(columna + 1.0, fila, 0.0);
			glVertex3d(columna + 1.0, fila + 1.0, 0.0);
			glVertex3d(columna, fila + 1.0, 0.0);
			glEnd();
			glEnable(GL_LIGHTING);
		}
	}

	//Dibuja las piezas comidas
	int Columna = 0;
	int FilaB = 8, FilaN = 8;
	int Fila = 8;
	int blancas = 0, negras = 0;
	for (int i = 0; i < 30; i++)
	{
		if (Comidas[i] != nullptr)
		{
			if (Comidas[i]->getColor() == 0)
			{
				if (blancas <= 7) Columna = -1;
				else
				{
					if (blancas == 8) FilaB = 8;
					Columna = -2;
				}
				Fila = FilaB--;
				blancas++;
			}
			else
			{
				if (negras <= 7)  Columna = 9;
				else
				{
					if (negras == 8) FilaN = 8;
					Columna = 10;
				}
				Fila = FilaN--;
				negras++;
			}
			glTranslatef(Columna, Fila, 0);
			Comidas[i]->dibuja();
			glTranslatef(-Columna, -Fila, 0);
		}
	}

	fondo.setCenter(4, 4);
	fondo.setSize(20, 20);
	fondo.draw();
}

