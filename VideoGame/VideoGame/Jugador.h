  #pragma once
using namespace System::Drawing;
#include "Escenario.h"
enum Direcciones { Arriba, Abajo, Izquierda, Derecha, Ninguna };//ninguna va ser la ultima tecla que presionemos 
class Jugador
{
public:

	Jugador(int x, int y) {
		//posicion del jugador
		this->x = x;
		this->y = y;
		//Movimiento del jugador 
		dx = 0;
		dy = 0;
		//Animacion del sprite
		ancho = 63;
		alto = 63;
		indiceX = 0;
		indiceY = 0;

		direccion = Direcciones::Ninguna;
		ultima = Direcciones::Abajo;


	}

	~Jugador();


	Rectangle retornarRectangulo() {
		return Rectangle(x + dx, y + 30, (ancho - 30), (alto - 30));
	}



	int getX() { return x; }
	int getY() { return y + 30 + dy; }





	void setDX(int dx) {
		this->dx = dx;
	}
	void setDY(int dy) {
		this->dy = dy;
	}





	void setDireccion(Direcciones direccion) {
		this->direccion = direccion;
	}
	void ValidarMovimiento(int** matriz) {
		int X, Y = 0;
		for (int i = 0;i < filas;i++) {
			X = 0;
			for (int j = 0;j < columnas;j++) {
				Rectangle c1 = Rectangle(X, Y, 50, 50);
				if (matriz[i][j] == 1 || matriz[i][j] == 3) {
					if (CDI.IntersectsWith(c1))dx = 0;
					if (CAA.IntersectsWith(c1))dy = 0;
				}
				X += 50;
			}
			Y += 50;
		}
	}

	void disminuirVidas() {
		x = 50;
		y = 50;
		vidas--;
	}
//------------------------------------------------------------------------------------------------------------------------------------------------------
	void disminuirvidas(int PuntaIzquierda, int PuntaDerecha, int CentroInicioY, int CentroFinalY, int PuntaSuperior, int PuntaInferior,
		int CentroInicioX, int CentroFinalX) {

		if (getX() >= PuntaIzquierda && getX() <= PuntaDerecha && getY() >= CentroInicioY && getY() <= CentroFinalY){
		//Toda la parte de el sprite bomba horizontal
			x = 50;
			y = 50;
			vidas--;
		}
		if (getY() >= PuntaSuperior && getY() <= PuntaInferior && getX() >= CentroInicioX && getX() <= CentroFinalX) {
			//Toda la parte de el sprite bomba vertical
			x = 50;
			y = 50;
			vidas--;
		}
}


//---------------------------------------------------------------------------------------------------

	void dibujarJugador(Graphics^g, Bitmap^ bmpJugador, int** matriz) {
		CDI = Rectangle(x + dx, y + 30 , (ancho-30 ), (alto -30) );
		CAA = Rectangle(x , y + 30  + dy, (ancho-30), (alto -30 ));


		g->DrawRectangle(Pens::Red, CDI);	
		g->DrawRectangle(Pens::Orange, CAA);

		

		ValidarMovimiento(matriz);//ir antes que el jugador 
		//thread th1(ValidarMovimiento, matriz);


		Rectangle PorcionAUsar = Rectangle(indiceX * ancho, indiceY * alto, ancho, alto);
		Rectangle Aumento = Rectangle(x-14, y, ancho, alto);///Dibujo del jugador --------------------------------
		g->DrawImage(bmpJugador, Aumento, PorcionAUsar, GraphicsUnit::Pixel);
		//desplazamiento
		x += dx;
		y += dy;

		//th1.join();

	}


	void moverJugador(Graphics^g, Bitmap^ bmpJugador, int** matriz) {
		//direccion == Arriba ? ancho = 17 : ancho = 18;//para eliminar el reflejo

		switch (direccion)
		{
		case Direcciones::Arriba:
			indiceY = 3; // ----------SEGUN V..ES 0  
			if (indiceX >= 0 && indiceX < 3)
				indiceX++;
			else
				indiceX = 1;
			dx = 0;
			dy = -10;
			ultima = Arriba;
			break;
		case Direcciones::Abajo:     
			indiceX = 0;
			if (indiceY >= 1 && indiceY < 3)
				indiceY++;
			else
				indiceY = 0;
			dx = 0;
			dy = 10;
			ultima = Abajo;
			break;

		case Direcciones::Izquierda:
			indiceY = 1;
			if (indiceX >= 1 && indiceX < 3)
				indiceX++;
			else
				indiceX = 1;
			dx = -10;
			dy = 0;
			ultima = Izquierda;
			break;																											

		case Direcciones::Derecha:
			indiceY = 2;
			if (indiceX >= 1 && indiceX < 3)
				indiceX++;
			else
				indiceX = 1;
			dx = 10;
			dy = 0;
			ultima = Derecha;
			break;




		case Direcciones::Ninguna:
			dx = dy = 0;
			if (ultima == Direcciones::Abajo) {
				indiceX = 0;
				indiceY = 0;
			}
			if (ultima == Direcciones::Arriba) {
				indiceX = 3;
				indiceY = 0;
			}
			if (ultima == Direcciones::Derecha) {
				indiceX = 2;
				indiceY = 0;
			}
			if (ultima == Direcciones::Izquierda) {
				indiceX = 1;
				indiceY = 0;
			}
			break; // Hasta ahi todo bien.
		default:
			break;
		}


			dibujarJugador(g, bmpJugador, matriz);//para que cada jugador no haga accion en eiempo distinto / Para que no exista problemas en relacion a la variacion al tiempo
		

	}
private:
	int x;
	int y;
	int dx;
	int dy;
	int ancho;
	int alto;
	int indiceX;
	int indiceY;
	Direcciones direccion;
	Direcciones ultima;

	Rectangle CDI;
	Rectangle CAA;

	//conteo de vidas 
	int vidas;
};



