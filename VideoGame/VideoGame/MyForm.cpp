#include "MyForm.h"
#include<thread>

using namespace VideoGame;

void FORM() {
	
	thread th3(Application::EnableVisualStyles); // utiliza thread para separar en un subproceso la creacion
												 // de estilos visuales para la aplicaci�n de colores, las fuentes , demas elementos visuales
												 //  todo en caso de haber un error , y permita correr el c�digo y se vea al menos de manera �spera

	Application::Run(gcnew MyForm());

	th3.join();
}
