#include "MyForm.h"
#include<thread>

using namespace VideoGame;

void FORM() {
	
	thread th3(Application::EnableVisualStyles); // utiliza thread para separar en un subproceso la creacion
												 // de estilos visuales para la aplicación de colores, las fuentes , demas elementos visuales
												 //  todo en caso de haber un error , y permita correr el código y se vea al menos de manera áspera

	Application::Run(gcnew MyForm());

	th3.join();
}
