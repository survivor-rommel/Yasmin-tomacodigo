#pragma once
#include "Control.h"
namespace VideoGame {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Media;

	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	private:
		//SoundPlayer^ MusicaN;
		Controladora* oControladora = new Controladora();
		Bitmap^ bmpSolido = gcnew Bitmap("MATERIALES\\bmpSolido.png");
		Bitmap^ bmpDestruible = gcnew Bitmap("MATERIALES\\bmpDestruible.png");
		Bitmap^ bmpSuelo = gcnew Bitmap("MATERIALES\\bmpSuel.png");
		//declaramos nuestra variable de lo que es el juegador 
		Bitmap^ bmpJugador = gcnew Bitmap("MATERIALES\\pika.png");
		Bitmap^ bmpCaja = gcnew Bitmap("MATERIALES\\caja.png");
		Bitmap^ bmpExplosion = gcnew Bitmap("MATERIALES\\explosion.png");

		Bitmap^ bmpEnemigo = gcnew Bitmap("MATERIALES\\bmpEnemigo.png"); 
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: agregar código de constructor aquí
			//

			//QUITAR EL FONDO EN LA POSICION DE COLOR..
			bmpJugador->MakeTransparent(bmpJugador->GetPixel(0, 0));


			bmpCaja->MakeTransparent(bmpCaja->GetPixel(0, 0));


			bmpExplosion->MakeTransparent(bmpExplosion->GetPixel(0, 0));

			bmpEnemigo->MakeTransparent(bmpEnemigo->GetPixel(0, 0));
		}


	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Timer^ timer1;
	protected:
	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Enabled = true;
			this->timer1->Tick += gcnew System::EventHandler(this, &MyForm::timer1_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(862, 749);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyDown);
			this->KeyUp += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::MyForm_KeyUp);
			this->ResumeLayout(false);

		}
#pragma endregion
		/*void Musican() {
			MusicaN = gcnew SoundPlayer("MATERIALES\\ModoSolitario.war");
			MusicaN->PlayLooping();
		}*/


	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
		oControladora->CambiarNivel();
	
	}

	private: System::Void timer1_Tick(System::Object^ sender, System::EventArgs^ e) {
		Graphics^ g = this->CreateGraphics();
		BufferedGraphicsContext^ espacio = BufferedGraphicsManager::Current;
		BufferedGraphics^ buffer = espacio->Allocate(g, this->ClientRectangle);

		/*Musican();*/


		oControladora->dibujar(buffer->Graphics, bmpSuelo, bmpSolido, bmpCaja, bmpExplosion, bmpDestruible, bmpJugador, bmpEnemigo);
		buffer->Render(g);
		delete buffer, espacio, g;

		

		
	}
	private: System::Void MyForm_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::Up:
			oControladora->getoJugador()->setDireccion(Direcciones::Arriba);
			break;
		case Keys::Down:
			oControladora->getoJugador()->setDireccion(Direcciones::Abajo);
			break;
		case Keys::Left:
			oControladora->getoJugador()->setDireccion(Direcciones::Izquierda);
			break;
		case Keys::Right:
			oControladora->getoJugador()->setDireccion(Direcciones::Derecha);
			break;
		default:
			break;
		}
	}
	private: System::Void MyForm_KeyUp(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		switch (e->KeyCode)
		{
		case Keys::Space:
			oControladora->agregarBomba();
			break;
		default:
			oControladora->getoJugador()->setDireccion(Direcciones::Ninguna);
			break;
		}
	}
		   /*
	private: System::Void trCarga_Tick(System::Object^ sender , System::EventArgs^ e){
		lblNivel->Text = "Nivel : " + oControladora->getNivel();
		pbCarga->Increment(10);
		if
	}
	*/
};
}
