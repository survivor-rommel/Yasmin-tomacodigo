#pragma once
#ifndef _ESCENARIO_H_
#define _ESCENARIO_H_


#define filas 15
#define columnas 17


#include <ctime>
#include<stdlib.h>

using namespace System::Drawing;


class Escenario
{
public:
	Escenario() {
		matriz = new int* [filas];
	}
	~Escenario();

	void generarMatriz() {

		srand(time(NULL()));
		for (int i = 0;i < filas;i++) {

			matriz[i] = new int[columnas];

		}


		for (int i = 0;i < filas;i++) {  //		

			for (int j = 0;j < columnas;j++) {

				if (i == 0 || j == 0 || i == filas - 1 || j == columnas - 1)//Bordes
					matriz[i][j] = 1;
				else {
					if (i % 2 == 0 && j % 2 == 0)//bloques fijos del interior
						matriz[i][j] = 1;

					else {

						if ((i == 1 && (j == 1 || j == 2)) || (j == 1 && i == 2) || (i == filas - 2 && (j == columnas - 3 || j == columnas - 2)) || (i == filas - 3 && j == columnas - 2))//zona movible
							matriz[i][j] = 0;
						else //Zonas que quedan (dependiendo de su valor seran destruibles o no)//2-es libre//3-destruibles
							matriz[i][j] = rand() % 2 + 2;

					}
				}
			}
		}
	}

	void PintarBase(Graphics^ g, Bitmap^ bmpBase) {

		int X, Y = 0;
		for (int i = 0;i < filas;i++) {
			X = 0;
			for (int j = 0;j < columnas;j++) {
				if (matriz[i][j] == 0 || matriz[i][j] == 2) {
					g->DrawImage(bmpBase, X, Y, 50, 50);

				}
				X += 50;
			}
			Y += 50;
		}
	}




	void PintarMatriz(Graphics^ g, Bitmap^ bmpSolido, Bitmap^ bmpDestruible) {

		int X, Y = 0;
		for (int i = 0;i < filas;i++) {
			X = 0;
			for (int j = 0;j < columnas;j++) {
				if (matriz[i][j] == 1) {
					g->DrawImage(bmpSolido, X, Y, 50, 50);
				}
				else {
					if (matriz[i][j] == 3) {
						g->DrawImage(bmpDestruible, X, Y, 50, 50);
					}
				}
				X += 50;
			}
			Y += 50;
		}
	}
	/*
	// funcion de Prueba - >  Funcion ---> transformar los bloques al tocar jugador 
	void trasnform_base(Graphics^g , Bitmap^ bmpSolido , Bitmap^ bmpDestruible)
	{
		int x = 0 , y  = 0  ,z = 0;
		if()
	}
	*/


	int** getmatriz() {
		return matriz;
	}

private:
	int** matriz;
};

#endif // !_ESCENARIO_H_