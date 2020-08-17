#pragma once

#include<iostream>
#include<memory>
#include<thread>
#include "Escenario.h"
#include"Jugador.h"
#include "ACajas.h"
#include "Enemigo.h"
#include "Calavera.h"
#include <vector>
//#include"ArrEnemigos.h"

class Controladora
{
public:
	Controladora() {
		
	
		oEscenario = new Escenario();
		oJugador = new Jugador(50, 50);//Aqui es donde el jugador iniciara la partida
		oArrBombas = new ACajas();
		//oJugador = make_shared<Jugador>(50,50);
		//oEscenario = make_shared<Escenario>();
		//oArrBombas = make_shared<ACajas>();
		oEnemigo = make_shared<Enemigo>();
		cant = 0;
		//oCalavera = new Calavera * [cant];

		//oArrEnemigos = new ArrEnemigos();
			

		nivel = 1;
	}
	~Controladora();
	void CambiarNivel() {
		thread esce(&Escenario::generarMatriz, oEscenario); // se crea un hilo , para  que se cree un subproceso al momento de generar el mapa , 
															// ya sea en cualquier caso de error funcional
		esce.join();
	}

	/*void crear_enemigos(){
		oArrEnemigos->crearEnemigos();
	}*/

	void agregarBomba() {
		//oArrBombas->crear_una_bomba(oJugador->getX(), oJugador->getY());
		thread crearbomba(&ACajas::crear_una_bomba, oArrBombas, oJugador->getX(), oJugador->getY());  // se hace un subproceso debido a que en el caso se implemente el caso de almacenar 
																								 	  // varias bombas , se puede tener un control al momento de la aparicion

		crearbomba.join();

	

	}

	 void disminuir_Vidas_Por_Bomba() {
		int PuntaIzquierda, PuntaDerecha, CentroInicioY, CentroFinalY, PuntaSuperior, PuntaInferior,
			CentroInicioX, CentroFinalX;
		///////////////////////////-------------------------//////////////////////////////////
		for (int i = 0;i < oArrBombas->getarregloBombas().size();i++) {

			PuntaIzquierda = oArrBombas->getarregloBombas().at(i)->getX() - 100;
			PuntaDerecha = oArrBombas->getarregloBombas().at(i)->getX() + 150;
			PuntaSuperior = oArrBombas->getarregloBombas().at(i)->getY() - 100;
			PuntaInferior = oArrBombas->getarregloBombas().at(i)->getY() + 150;
			CentroInicioY = oArrBombas->getarregloBombas().at(i)->getY();
			CentroInicioX = oArrBombas->getarregloBombas().at(i)->getX();
			CentroFinalX = oArrBombas->getarregloBombas().at(i)->getX() + 50;
			CentroFinalY = oArrBombas->getarregloBombas().at(i)->getY() + 50;
			
			if (oArrBombas->getarregloBombas().at(i)->getEstado() == Estado::explosion) {
				thread dismiVidas2(&Jugador::disminuirvidas, oJugador, PuntaIzquierda, PuntaDerecha, CentroInicioY, CentroFinalY, PuntaSuperior, PuntaInferior,
					CentroInicioX, CentroFinalX);
			// Se toma como un subprocesola disminución de vida del Jugador(muerte) , de modo de que no se al completo dependiente del caso de morir por enemigo o por bomba
				


			//	oJugador->disminuirvidas(PuntaIzquierda, PuntaDerecha, CentroInicioY, CentroFinalY, PuntaSuperior, PuntaInferior,
			//		CentroInicioX, CentroFinalX);
				dismiVidas2.join();
			}
		}

		
	}

	void disminuir_Vidas_Por_Enemigo(){
		if(oJugador->retornarRectangulo().IntersectsWith(oEnemigo->retornarRectangulo())){
			thread dismiVida(&Jugador::disminuirVidas, oJugador);
			dismiVida.join();  // al momento de disminuir la vida , se hace un subproceso , para que en el caso de que en el mismo momento la bomba y el enemigo colisionen
								// con nuestro personaje , se puede ejecutar ambas funciones de darse el caso. , tomando ambos casos de manera mas organizada
			
		}
	}

	void dibujar(Graphics^ g, Bitmap^ bmpBase, Bitmap^ bmpSolido, Bitmap^ bmpBomba, Bitmap^ bmpExplosion, Bitmap^ bmpDestruible, Bitmap^ bmpJugador, Bitmap^ bmpEnemigo) {

		// Aqui por medio de threads vamos a dividr el dibujo de nuesto escenario total en subprocesos , en caso de ocurrir erroer
		
		oEscenario->PintarBase(g, bmpBase);
		oEscenario->PintarMatriz(g, bmpSolido, bmpDestruible);

		oJugador->moverJugador(g, bmpJugador, oEscenario->getmatriz());
		
		oArrBombas->dibujar_una_bomba(g, bmpBomba, bmpExplosion, oJugador->getX(), oJugador->getY(), oEscenario->getmatriz());




		oEnemigo->dibujar(g, bmpEnemigo,  oEscenario->getmatriz());
		oEnemigo->animar();

		// Se dividira el trabajo de disminuir la vida por bomba y enemigo en subprocesos distintos
		// con lo que adicionalemente se brindara un tiempe entre subprocesos al momento desaparecer si nos toca el enemigo o la bomba o ambos 

		thread dEnemigo(&Controladora::disminuir_Vidas_Por_Enemigo,this);	
		thread dBomba(&Controladora::disminuir_Vidas_Por_Bomba,this); // parametro es "this" , ya que llama a una funcion de la propia clase , y no se puede trabajar por medio
																	  // de una instanciación


		dEnemigo.join();
		dBomba.join();
	}

	
	/*void crear_enemigos_y_mejoras(){
		oArrEnemigos->crearEnemigos();
	}*/
	



	Jugador* getoJugador() {
		return oJugador;
	}
	
	shared_ptr<Enemigo> getoEnemigo() {
		return oEnemigo;
	}

	/*ArrEnemigos  *getoArrEnemigos(){
		return oArrEnemigos;
	}*/

	int getNivel() {
		return nivel;
	}
	




	/*

	//////////////////////////////////////////////////
	void MoverGatos(Graphics^ g)
	{
		for (int i = 0;i < cant;i++) {
			if (oCalavera[i]->GetX() > oJugador->GetX())
				oCalavera[i]->Mover(Direccion::Izquierda, g);

			else if (oCalavera[i]->GetX() < oJugador->GetX())
				oCalavera[i]->Mover(Direccion::Derecha, g);



			if (oCalavera[i]->GetY() > oJugador->GetY())
				oCalavera[i]->Mover(Direccion::Arriba, g);

			else if (oCalavera[i]->oJugador() < paloma->GetY())
				oCalavera[i]->Mover(Direccion::Abajo, g);
		}
	}

	void MostrarCalaveras(Graphics^ g, Bitmap^ img)
	{
		for (int i = 0;i < cant;i++) {
			oCalavera[i]->Mostrar(g, img);
		}
		//oJugador->MoverBalas();
	}

	void AgregarGatos(int n)//agregando elementos a un arreglo 
	{
		for (int m = 0;m < n;m++) {

			Calavera** aux = new Calavera * [cant + 1];

			for (int i = 0;i < cant;i++)
				aux[i] = oCalavera[i];

			aux[cant] = new Calavera();

			oCalavera = aux;
			cant++;
		}
	}

	////////////////////////////////////////////////////////////////////////

	*/


private:
	Escenario* oEscenario;
	Jugador* oJugador;
	ACajas* oArrBombas;

	//Enemigo *oEnemigo;
	
	//shared_ptr<Jugador> oJugador;
	//shared_ptr<Escenario> oEscenario;
	//shared_ptr<ACajas> oArrBombas;
	shared_ptr<Enemigo> oEnemigo;

	//Calavera** oCalavera;  // 
	





	int cant;
	//ArrEnemigos *oArrEnemigos;
	int nivel;

};





