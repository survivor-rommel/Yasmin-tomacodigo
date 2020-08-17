#pragma once

#include "Enemigo.h"
#include<vector>

using namespace std;

class ArrEnemigos {

public:
	ArrEnemigos(){
		arregloEnemigos = vector<Enemigo*>();
	}
	~ArrEnemigos(){}

	void  crearEnemigos(){
		Enemigo* nuevo = new Enemigo();
		arregloEnemigos.push_back(nuevo);
	}


	void dibujar (Graphics ^g ,Bitmap^bmpEnemigo , int **matriz){
		/*for (auto &elem : arregloEnemigos) {
			arregloEnemigos.at(i)->dibujar(g, bmpEnemigo, matriz);
			arregloEnemigos.at(i)->animar();
		}*/

		for(int i = 0 ; i < arregloEnemigos.size() ; i++){
			arregloEnemigos.at(i)->dibujar(g, bmpEnemigo, matriz);
			arregloEnemigos.at(i)->animar();
		}
	}
	vector<Enemigo*> getarregloEnemigos(){
		return arregloEnemigos;
	}
private:
	vector<Enemigo*> arregloEnemigos;

};