
using namespace System::Drawing;

enum Estado { normal, explosion, desaparecer };
class CajaB
{
public:
	CajaB(int x, int y) {
		this->x = x;
		this->y = y;

		estado = Estado::normal;

		ancho = 467 / 3;//propiedades de la imagen 66x24 //66 entre las imagenes que se tiene
		alto = 184;

		indiceX = 0;
		tiempo_antes_de_explotar = 0;

		//datos iniciales para la explosion
		indiceEX = 0;
		indiceEY = 0;
		altoExplosion = 160 / 8;
		anchoExplosion = 80 / 4;
	}
	~CajaB();

	bool validarLugar(int xJugador, int yJugador, int** matriz) {
		if (matriz[yJugador / 50][xJugador / 50] == 0 || matriz[yJugador / 50][xJugador / 50] == 2)
			return true;
		else
			return false;
	}


	void dibujarBomba(Graphics^ g, Bitmap^ bmpBomba, int xJugador, int yJugador, int** matriz) {
		if (validarLugar(xJugador, yJugador, matriz) == true) {
			Rectangle porcionAUsar = Rectangle(indiceX * ancho, 0, ancho, alto);
			Rectangle aumento = Rectangle(x, y, 50, 50 );
			g->DrawImage(bmpBomba, aumento, porcionAUsar, GraphicsUnit::Pixel);

		}

		if (tiempo_antes_de_explotar == 6) { estado = Estado::explosion; }
	}






	void animar() {
		if (indiceX >= 0 && indiceX < 2)
			indiceX++;
		else {
			tiempo_antes_de_explotar++;
			indiceX = 0;
		}
	}


	void DibujarExplosion(Graphics^ g, Bitmap^ bmpExplosionCentro, int** matriz) {

		Rectangle porcionUsarCentro = Rectangle(indiceEX * anchoExplosion, indiceEY * altoExplosion, anchoExplosion, altoExplosion); // indiceY=0
		Rectangle centro = Rectangle(x, y, 50, 50);
		g->DrawImage(bmpExplosionCentro, centro, porcionUsarCentro, GraphicsUnit::Pixel);
		if (matriz[y / 50][(x - 50) / 50] != 1) {
			Rectangle porcionUsarIzquierda = Rectangle(indiceEX * anchoExplosion, indiceEY + 2 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 2
			Rectangle izquierda = Rectangle(x - 50, y , 50, 50);
			g->DrawImage(bmpExplosionCentro, izquierda, porcionUsarIzquierda, GraphicsUnit::Pixel);

			if (matriz[y / 50][(x - 50) / 50] == 3) { matriz[y / 50][(x - 50) / 50] = 2; }
		}


		if (matriz[y / 50][(x + 50) / 50] != 1) {
			Rectangle porcionUsarDerecha = Rectangle(indiceEX * anchoExplosion, indiceEY + 4 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 4
			Rectangle derecha = Rectangle(x + 50, y , 50, 50);
			g->DrawImage(bmpExplosionCentro, derecha, porcionUsarDerecha, GraphicsUnit::Pixel);

			if (matriz[y / 50][(x + 50) / 50] == 3) { matriz[y / 50][(x + 50) / 50] = 2; }

		}
		if (matriz[y / 50][(x + 50) / 50] != 1) {
			Rectangle porcionUsarPuntaDerecha = Rectangle(indiceEX * anchoExplosion, indiceEY + 3 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 3
			Rectangle Puntaderecha = Rectangle(x + 100, y, 50, 50);
			g->DrawImage(bmpExplosionCentro, Puntaderecha, porcionUsarPuntaDerecha, GraphicsUnit::Pixel);

			if (matriz[y / 50][(x + 100) / 50] == 3 && matriz[y / 50][(x + 50) / 50] != 1)
			{

				matriz[y / 50][(x + 100) / 50] = 2;
			}
		}

		if (matriz[y / 50][(x - 50) / 50] != 1) {
			Rectangle porcionUsarPuntaIzquierda = Rectangle(indiceEX * anchoExplosion, indiceEY + 1 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 1
			Rectangle Puntaizquierda = Rectangle(x - 100, y , 50, 50);
			g->DrawImage(bmpExplosionCentro, Puntaizquierda, porcionUsarPuntaIzquierda, GraphicsUnit::Pixel);

			if (matriz[y / 50][(x - 100) / 50] == 3 && matriz[y / 50][(x - 50) / 50] != 1)
			{
				matriz[y / 50][(x - 100) / 50] = 2;
			}
		}

		Rectangle porcionUsarVerticales = Rectangle(indiceEX * anchoExplosion, indiceEY + 6 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 1
		Rectangle VerticalSuperior = Rectangle(x, y - 50 , 50, 50);
		Rectangle VerticalInferior = Rectangle(x, y + 50 , 50, 50);

		if (matriz[(y - 50) / 50][x / 50] != 1) { g->DrawImage(bmpExplosionCentro, VerticalSuperior, porcionUsarVerticales, GraphicsUnit::Pixel); }
		if (matriz[(y - 50) / 50][x / 50] == 3) { matriz[(y - 50) / 50][x / 50] = 2; }
		if (matriz[(y + 50) / 50][x / 50] != 1) { g->DrawImage(bmpExplosionCentro, VerticalInferior, porcionUsarVerticales, GraphicsUnit::Pixel); }
		if (matriz[(y + 50) / 50][x / 50] == 3) { matriz[(y + 50) / 50][x / 50] = 2; }


		if (matriz[(y - 50) / 50][x / 50] != 1) {
			Rectangle porcionUsarPuntaSuperior = Rectangle(indiceEX * anchoExplosion, indiceEY + 5 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 5
			Rectangle PuntaSuperior = Rectangle(x, y - 100 , 50, 50);
			g->DrawImage(bmpExplosionCentro, PuntaSuperior, porcionUsarPuntaSuperior, GraphicsUnit::Pixel);

			if (matriz[(y - 100) / 50][x / 50] == 3 && matriz[(y - 50) / 50][x / 50] != 1) { matriz[(y - 100) / 50][x / 50] = 2; }
		}


		if (matriz[(y + 50) / 50][x / 50] != 1) {
			Rectangle porcionUsarPuntaInferior = Rectangle(indiceEX * anchoExplosion, indiceEY + 7 * altoExplosion, anchoExplosion, altoExplosion); //indiceY = 7
			Rectangle PuntaInferior = Rectangle(x, y + 100 , 50, 50);
			g->DrawImage(bmpExplosionCentro, PuntaInferior, porcionUsarPuntaInferior, GraphicsUnit::Pixel);
			if (matriz[(y + 100) / 50][x / 50] == 3 && matriz[(y + 50) / 50][x / 50] != 1) {
				matriz[(y + 100) / 50][x / 50] = 2;
			}
		}
	}




	void animarExplosion() {
		if (indiceEX >= 0 && indiceEX < 3) {
			indiceEX++;
		}
		else {
			estado = Estado::desaparecer;
		}
	}


	Estado getEstado() {
		return estado;
	}

	int getX() {
		return x;
	}
	int getY() {
		return y;
	}


private://datos de la explosion
	int indiceEX;
	int indiceEY;


	int altoExplosion;
	int anchoExplosion;

private://daros de la bomba
	int x;
	int y;

	int ancho;
	int alto;
	int indiceX;//no indiceY por que la imagen es de una linea

	int tiempo_antes_de_explotar;
	Estado estado;
};

