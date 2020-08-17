#pragma once

#include<ctime>
#include<stdlib.h>

using namespace System::Drawing;
class Mejora {

public:
	Mejora() {
		ubicado = false;
		i = rand() % 13 + 1; // ubicacion aleaotoria en la matriz 
		j = rand() % 15 + 1; // muros solidos no cuentan 
	
		ancho = 128 / 8; // variable segun la imagen
		alto = 96 / 6;
		
		indiceX = 0;
		indiceY = 0;
	}
	~Mejora(){}
	void dibujar(Graphics^g,Bitmap^bmpMejoras , int **matriz){ // matriz , ubicacion de la mejora
		Rectangle porcionAUsar = Rectangle(indiceX  *  ancho, indiceY * alto, ancho, alto);

		while(ubicado == false){
			if (matriz[i][j] == 3) { // verifica si esta en un bloque destructible
				ubicado = true;
}
			else{

			}
		}
	}



private:
	int i;
	int j;
	
	int indiceX;
	int indiceY;

	int ancho;
	int alto;

	int tipo_de_mejora;   //diferencia mejora que estamos usando actualmente
	bool ubicado;  // saber si se ubico o no la mejora en la matriz(escenario)
};