#pragma once
#pragma once

#include "CajaB.h"
#include <vector>
using namespace std;

class ACajas
{
public:
	ACajas() { totalBombas = 1; }
	~ACajas();
	void crear_una_bomba(int x, int y) {
		if (arregloBombas.size() < totalBombas) {
			CajaB* nueva_bomba = new CajaB(x, y);
			arregloBombas.push_back(nueva_bomba);
		}
	}
	void dibujar_una_bomba(Graphics^ g, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, int xJugador, int yJugador, int** matriz) {
		for (int i = 0;i < arregloBombas.size();i++) {
			switch (arregloBombas.at(i)->getEstado())
			{
			case Estado::normal:
				arregloBombas.at(i)->dibujarBomba(g, bmpBomba, xJugador, yJugador, matriz);
				arregloBombas.at(i)->animar();
				break;
			case Estado::explosion:
				arregloBombas.at(i)->DibujarExplosion(g, bmpExplosion, matriz);
				arregloBombas.at(i)->animarExplosion();
				break;
			case Estado::desaparecer:
				arregloBombas.erase(arregloBombas.begin() + i);
				break;

			}
		}
	}


	vector<CajaB*>getarregloBombas() {
		return arregloBombas;
	}
private:
	vector<CajaB*>arregloBombas;
	int totalBombas;


};

