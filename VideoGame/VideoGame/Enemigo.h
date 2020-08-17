#pragma once

#include<ctime>
#include<stdlib.h>


using namespace System::Drawing;


class Enemigo {
public:
	Enemigo() {
		srand(time(NULL));
		i = rand() % 13 + 1;  // enemigo .. > movimiento aleatorio
		j = rand() % 13 + 2;
		x = 715;// ubicacion aleatoria
		y = 650;
		dx = 5;
		indiceX = 0;
		indiceY = 0;
		
		ancho = 96/6; //
		alto = 16;  
		ubicado = false;
		
	}
	~Enemigo() {}
	void dibujar(Graphics^ g, Bitmap^ bmpEnemigo, int** matriz) {
		Rectangle porcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		while ((matriz[i][j - 1] != 2 || matriz[i][j] != 2 || matriz[i][j + 1] != 2) && i < 14 && ubicado == false) {     // posicion x y y aleatoria , posicion del enemigo no debe estar en un bloque no destructible                                                                                                                                                                                                                                                                                                                                      2:ubicado==false){
			j++; // se reduce en j , ya que el movimiento sera en X , izquierdad - derecha 
			if (j == 15) {
				i++; //la fila aumenta
				j = 0;   // vuelve a la columna inicial
			}
			if (i >= 14) break; // si la fila no se encuentra , sale del bucle
			x = j * 50;
			y = i * 50;
		}
		
		Rectangle Aumento = Rectangle(x, y, 40, 40); // almacena posicion en x y en y




		//-------------------------------------------------------------------------------------------------------------

		g->DrawImage(bmpEnemigo, Aumento, porcionAUsar, GraphicsUnit::Pixel);



		  // para que siga el ciclo 
		x += dx; // movimiento enemigo en horizontal
		if ((matriz[y / 50][(x + 50) / 50] == 3 || matriz[y / 50][(x + 50 / 50)] == 1) || (matriz[y / 50][(x - 10) / 50] == 3 || matriz[y / 50][(x - 10) / 50] == 1))
			dx *= -1; // para el rebote
		
	}// -1 par que se note el rebote
	//----------------------------------------------------------------------------------------------------------------------------------------------




	void animar() {
		if (indiceX >= 0 && indiceX < 5) {
			indiceX++;
		}
		if (indiceX == 5) {
			while (indiceX != 0) {
				indiceX--; // tiene retroceder hasta que sea cero ,para que llegar al final de la imagen(sprite) regrese al final de manera inversa y no de manera inmediata
			}
		}
	}
	Rectangle retornarRectangulo(){
		return Rectangle(x, y, 50, 50);
	}
private:

	int x;
	int y;

	int i;
	int j;

	int dx;

	int indiceX;
	int indiceY;

	int ancho;
	int alto;


	bool ubicado;
	
};
