#pragma once

#include "Control.h"" 
using namespace System;   // agregado Rommel ->BORRAR
using namespace System::Drawing;

//enum Estado_Enemigo { Eliminado, Normal }; // agregado Rommel ->BORRAR
//enum Direccion  {Arriba,Abajo,Izquierda,Derecha}; // agregado Rommel ->BORRAR

class Calavera {
public:

	Calavera() {
		Random j;
		i = j.Next(100, 500);
		System::Threading::Thread::Sleep(10);
		jj = j.Next(200, 500);//posicion del gato al inicio
		System::Threading::Thread::Sleep(10);
		dx = 5;
		indiceX = 0;
		indiceY = 0;
		ancho = 96 / 6; //
		alto = 16;
		ubicado = false;

	}

	~Calavera();


	void dibujar(Graphics^ g, Bitmap^ bmpEnemigo, int** matriz) {
		Rectangle porcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		while ((matriz[i][jj - 1] != 2 || matriz[i][jj] != 2 || matriz[i][jj + 1] != 2) && i < 14 && ubicado == false) {     // posicion x y y aleatoria , posicion del enemigo no debe estar en un bloque no destructible                                                                                                                                                                                                                                                                                                                                      2:ubicado==false){
			jj++; // se reduce en j , ya que el movimiento sera en X , izquierdad - derecha 
			if (jj == 15) {
				i++; //la fila aumenta
				jj = 0;   // vuelve a la columna inicial
			}
			if (i >= 14) break; // si la fila no se encuentra , sale del bucle
			x = jj * 50;
			y = i * 50;
		}

		Rectangle Aumento = Rectangle(x, y, 40, 40); // almacena posicion en x y en y




		//-------------------------------------------------------------------------------------------------------------

		g->DrawImage(bmpEnemigo, Aumento, porcionAUsar, GraphicsUnit::Pixel);



		// para que siga el ciclo 
		x += dx; // movimiento enemigo en horizontal

		y += dy;

		if ((matriz[y / 50][(x + 50) / 50] == 3 || matriz[y / 50][(x + 50 / 50)] == 1) || (matriz[y / 50][(x - 10) / 50] == 3 || matriz[y / 50][(x - 10) / 50] == 1)) {
			dx *= -1; // para el rebote
			dy *= -1;
		}
	}// -1 par que se note el rebote
	//----------------------------------------------------------------------------------------------------------------------------------------------



private:
	int x;
	int y;

	int i;
	int jj;

	int dx;
	int dy;  // viene del SpriteTest // agregado Rommel ->BORRAR


	int indiceX;
	int indiceY;

	//int fila;     // viene del SpriteTest // agregado Rommel ->BORRAR
	//int columna;  // viene del SpriteTest // agregado Rommel ->BORRAR


	int ancho;
	int alto;

	bool ubicado;
	

};


