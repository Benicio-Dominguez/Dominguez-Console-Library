#include "Ventana.h"

#include <iostream>
#include <windows.h>
#include <vector>
#include "Widget.h"
#include "Consola.h"
#include "ImagenAscii.h"
#include "Entrada.h"
#include "Formato.h"
using namespace std;

const graficosCuadro  Ventana::simple{ '³','Ä','¿','Ú','À','Ù',' '}; //Inicializo los graficos simples, para verlos correctamente usar CP OEM854
const graficosCuadro  Ventana::doble{ 'º','Í','»','É','È','¼',' ' }; //Inicializo los graficos dobles, para verlos correctamente usar CP OEM854

Ventana::Ventana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, COORD tamano) {
	titulo = _titulo;
	posicionVentana = posicion;
	tamanoVentana = tamano;
	colorFondo = fondo;
	colorTexto = texto;
}

COORD Ventana::DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, COORD tamano) {
	Ventana temp(_titulo, posicion, fondo, texto, tamano);
	if (tamano.X == 0 && tamano.Y == 0)
		temp.CalcularTamano();
	return temp.DibujarVentana();
}

COORD Ventana::DibujarVentana() {
	COORD nuevaPosicion{0,0};

	ReiniciarConsola rc; //Creo un objeto ReiniciarConsola que al salir de la función reiniciará los colores.

	//Cambio el color para dibujar la ventana.
	Consola::ColorTexto(colorTexto);
	Consola::ColorFondo(colorFondo);

	Consola::MoverCursor(posicionVentana);

	//Dibujo la primera fila, con el título.
	cout << graficos.esquinaSupIzquierda;
	for (size_t i = 0; i < tamanoVentana.X - 2; i++)
	{
		if (i >= titulo.size())
			cout << graficos.horizontal;
		else
			cout << titulo.at(i);
	}
	cout << graficos.esquinaSupDerecha;

	//Creo un string que contiene la línea horizontal con el espaciado correcto.
	string lineaHorizontal;
	lineaHorizontal.push_back(graficos.vertical);
	for (int i = 1; i < tamanoVentana.X - 1; i++)
	{
		lineaHorizontal.push_back(graficos.relleno);
	}
	lineaHorizontal.push_back(graficos.vertical);

	//Imprimo el cuadro.
	for (int i = 0; i < tamanoVentana.Y - 2; i++)
	{
		nuevaPosicion = posicionVentana;
		nuevaPosicion.Y += i + 1;
		Consola::MoverCursor(nuevaPosicion);
		cout << lineaHorizontal;
	}

	nuevaPosicion.Y++;
	Consola::MoverCursor(nuevaPosicion);

	//Imprimo la última línea del cuadro.
	cout << graficos.esquinaInfIzquierda;
	for (int i = 0; i < tamanoVentana.X - 2; i++)
	{
		cout << graficos.horizontal;
	}
	cout << graficos.esquinaInfDerecha;

	nuevaPosicion = posicionVentana;
	nuevaPosicion.X++;
	nuevaPosicion.Y++;

	Consola::MoverCursor(nuevaPosicion);

	return nuevaPosicion;
}

void Ventana::MoverVentana(COORD nuevaPosicion) {
	posicionVentana = nuevaPosicion;
}

void Ventana::CambiarTamano(COORD nuevoTamano) {
	tamanoVentana = nuevoTamano;
}

void Ventana::CalcularTamano() {
	int largoMinimoX = 3;
	int largoMinimoY = 3;
	largoMinimoX = titulo.size() + 2;
	tamanoVentana.X = largoMinimoX;
	tamanoVentana.Y = largoMinimoY;
}

VentanaMensaje::VentanaMensaje(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, string aceptar, COORD tamano, imagenAscii* _imagen) : Ventana(_titulo, posicion, fondo, texto, tamano) {
	//Separo el mensaje en varios strings, usando '\n' de separador, para poder dimensionar la ventana correctamente.
	if (mensaje.at(mensaje.size() - 1) != '\n')
		mensaje += "\n";
	string delimitador = "\n";
	size_t pos = 0;
	std::string token;
	while ((pos = mensaje.find(delimitador)) != string::npos) {
		token = mensaje.substr(0, pos);
		mensajeAviso.push_back(token);
		mensaje.erase(0, pos + delimitador.length());
	}

	imagen = _imagen;
	mensajeAceptar = aceptar;
}

COORD VentanaMensaje::DibujarVentana() {
	COORD posicionOriginal = Ventana::DibujarVentana();
	COORD nuevaPosicion = posicionOriginal;
	ReiniciarConsola rc; //Creo un objeto ReiniciarConsola que al salir de la función reiniciaá los colores.

	//Si la ventana contiene una imagen, la imprime.
	if (imagen != NULL) {
		COORD temp = Consola::PosicionCursor();
		temp.Y++;	//Aumento Y para dejar un espacio entre la parte de arriba y la imagen.

		//Si hay suficiente espacio, centro la imagen.
		int espacio = ((tamanoVentana.X - imagen->Tamano().X) / 2) - 1;
		if (espacio > 0) {
			temp.X += espacio;
		}

		Consola::MoverCursor(temp);
		imagen->Mostrar();
	}

	//Cambio el color para dibujar la ventana.
	Consola::ColorTexto(colorTexto);
	Consola::ColorFondo(colorFondo);

	//Coloco el cursor en la posici¾n correcta para empezar a escribir el mensaje.
	if (imagen != NULL)
		nuevaPosicion.Y = Consola::PosicionCursor().Y + 1;
	else
		nuevaPosicion.Y = Consola::PosicionCursor().Y;
	nuevaPosicion.X = posicionOriginal.X;

	//Imprimo el mensaje.
	for (unsigned short int i = 0; i < mensajeAviso.size(); i++)
	{
		Consola::MoverCursor(nuevaPosicion);
		cout << mensajeAviso[i];
		nuevaPosicion.Y++;
	}

	//Agrego una tabulación variable para centrar el botón de aceptar.
	SHORT temp = (SHORT)(mensajeAviso.size() + 1);
	if (imagen != NULL)
		temp += imagen->Tamano().Y + 2;	//Agrego 2, porque se deja un espacio arriba y otro abajo de la imagen.
	Consola::MoverCursor({ posicionOriginal.X,  posicionOriginal.Y + temp });
	int espacio = (tamanoVentana.X - mensajeAceptar.size() - 3) / 2;

	if (espacio > 0) {
		COORD temp = Consola::PosicionCursor();
		temp.X += espacio;
		Consola::MoverCursor(temp);
	}

	cout << ">" << mensajeAceptar;

	//Me enclavo esperando a que el usuario toque enter.
	while (Entrada::EstadoTecla(tecla::Enter) != estadoTecla::presionada);

	return Consola::PosicionCursor();
}

void VentanaMensaje::CalcularTamano() {
	unsigned int largoMinimoX = 3;
	unsigned int largoMinimoY = 5;

	if (titulo.size() > largoMinimoX - 2)
		largoMinimoX = titulo.size() + 2;

	if (mensajeAceptar.size() > largoMinimoX - 3)
		largoMinimoX = mensajeAceptar.size() + 3; //Se agregan 3 y no 2 porque al mensaje de aceptar siempre se le antepone un '>'

	if (imagen != NULL) {
		if (imagen->Tamano().X > largoMinimoX - 2)
			largoMinimoX = imagen->Tamano().X + 4; //Le agrego 4 en lugar de dos, para dejar dos espacios de separaci¾n con los bordes.
	}
	for (unsigned int i = 0; i < mensajeAviso.size(); i++)
	{
		if (mensajeAviso[i].size() > largoMinimoX - 2)
			largoMinimoX = mensajeAviso[i].size() + 2;
	}

	largoMinimoY = mensajeAviso.size() + 4;

	if (imagen != NULL)
		largoMinimoY += imagen->Tamano().Y + 2;//Se le suma dos porque a la imagen se le deja un espacio abajo y otro arriba.

	tamanoVentana.X = largoMinimoX;
	tamanoVentana.Y = largoMinimoY;
}

void VentanaMensaje::CambiarMensaje(string mensaje) {
	mensajeAviso.clear();
	if (mensaje.at(mensaje.size() - 1) != '\n')
		mensaje += "\n";
	string delimitador = "\n";
	size_t pos = 0;
	std::string token;
	while ((pos = mensaje.find(delimitador)) != string::npos) {
		token = mensaje.substr(0, pos);
		mensajeAviso.push_back(token);
		mensaje.erase(0, pos + delimitador.length());
	}
}

COORD VentanaMensaje::DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, string aceptar, COORD tamano, imagenAscii* _imagen) {
	VentanaMensaje temp(_titulo, posicion, fondo, texto, mensaje, aceptar, tamano, _imagen);
	if (tamano.X == 0 && tamano.Y == 0)
		temp.CalcularTamano();
	return temp.DibujarVentana();
}

VentanaMenu::VentanaMenu(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, Menu* _menu, COORD tamano, imagenAscii* _imagen) : Ventana(_titulo, posicion, fondo, texto, tamano) {
	imagen = _imagen;
	menu = _menu;
}

unsigned int VentanaMenu::DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, Menu* _menu, COORD tamano, imagenAscii* _imagen) {
	VentanaMenu temp(_titulo, posicion, fondo, texto, _menu, tamano, _imagen);
	if (tamano.X == 0 && tamano.Y == 0)
		temp.CalcularTamano();
	return temp.DibujarVentana();
}

unsigned int VentanaMenu::DibujarVentana() {
	COORD posicionOriginal = Ventana::DibujarVentana();

	ReiniciarConsola rc; //Creo un objeto ReiniciarConsola que al salir de la función reiniciará los colores.

	//Si la ventana contiene una imagen, la imprime.
	if (imagen != NULL) {
		COORD temp = Consola::PosicionCursor();
		temp.Y++;	//Aumento Y para dejar un espacio entre la parte de arriba y la imagen.

					//Si hay suficiente espacio, centro la imagen.
		int espacio = ((tamanoVentana.X - imagen->Tamano().X) / 2) - 1;
		if (espacio > 0) {
			temp.X += espacio;
		}

		Consola::MoverCursor(temp);
		imagen->Mostrar();
	}

	//Coloco el cursor en la posici¾n correcta para empezar a escribir el mensaje.
	if (imagen != NULL)
		Consola::MoverCursor({ posicionOriginal.X, Consola::PosicionCursor().Y + 1 }); //Se suma uno para dejar espacio despuÚs de la imagen.
	else
		Consola::MoverCursor({ posicionOriginal.X, Consola::PosicionCursor().Y });

	//Cambio el color para dibujar la ventana.
	Consola::ColorTexto(colorTexto);
	Consola::ColorFondo(colorFondo);

	return menu->Mostrar();
}

void VentanaMenu::CalcularTamano() {
	int largoMinimoX = 3;
	int largoMinimoY = 5;

	largoMinimoX = titulo.size() + 2;

	if (imagen != NULL) {
		if (imagen->Tamano().X > largoMinimoX - 2)
			largoMinimoX = imagen->Tamano().X + 4; //Le agrego 4 en lugar de dos, para dejar dos espacios de separaci¾n con los bordes.
	}

	for (int i = 0; i < menu->CantidadElementos(); i++)
	{
		if (menu->LargoDe(i) > largoMinimoX - 2)
			largoMinimoX = menu->LargoDe(i) + 2 + 5 +1;	//El +5 es de la tabulaci¾n para cada elemento del men·. El +1 es del punto que se agrega al final de cada elemento del menú.
	}
	largoMinimoY = menu->CantidadElementos() + 2;
	if (imagen != NULL)
		largoMinimoY += 2 + imagen->Tamano().Y;//Se le suma 2 por el espacio que se deja encima y debajo de la imagen.
	tamanoVentana.X = largoMinimoX;
	tamanoVentana.Y = largoMinimoY;
}

VentanaEntrada::VentanaEntrada(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, CuadroEntrada* _mensajeFlotante, COORD tamano) : Ventana(_titulo, posicion, fondo, texto, tamano) {
	//Separo el mensaje en varios strings, usando '\n' de separador, para poder dimensionar la ventana correctamente.
	if (mensaje.at(mensaje.size() - 1) != '\n')
		mensaje += "\n";
	string delimitador = "\n";
	size_t pos = 0;
	std::string token;
	while ((pos = mensaje.find(delimitador)) != string::npos) {
		token = mensaje.substr(0, pos);
		mensajeAviso.push_back(token);
		mensaje.erase(0, pos + delimitador.length());
	}

	mensajeFlotante = _mensajeFlotante;
}

string VentanaEntrada::DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, CuadroEntrada* _mensajeFlotante, COORD tamano){
	VentanaEntrada temp(_titulo, posicion, fondo, texto, mensaje, _mensajeFlotante, tamano);
	if (tamano.X == 0 && tamano.Y == 0)
		temp.CalcularTamano();
	return temp.DibujarVentana();
}

string VentanaEntrada::DibujarVentana() {
	COORD posicionOriginal = Ventana::DibujarVentana();
	COORD nuevaPosicion = posicionOriginal;
	ReiniciarConsola rc; //Creo un objeto ReiniciarConsola que al salir de la función reiniciará los colores.

	//Cambio el color para dibujar la ventana.
	Consola::ColorTexto(colorTexto);
	Consola::ColorFondo(colorFondo);

	//Coloco el cursor en la posición correcta para empezar a escribir el mensaje.
	nuevaPosicion.Y = Consola::PosicionCursor().Y;
	nuevaPosicion.X = posicionOriginal.X;

	//Imprimo el mensaje.
	for (unsigned short int i = 0; i < mensajeAviso.size(); i++)
	{
		Consola::MoverCursor(nuevaPosicion);
		cout << mensajeAviso[i];
		nuevaPosicion.Y++;
	}

	//Agrego una tabulación variable para centrar el cuadro de entrada.
	SHORT temp = (SHORT)(mensajeAviso.size() + 1);
	Consola::MoverCursor({ posicionOriginal.X,  posicionOriginal.Y + temp });
	int espacio = (tamanoVentana.X - mensajeFlotante->Largo()- 2) / 2; 

	if (espacio > 0) {
		COORD temp = Consola::PosicionCursor();
		temp.X += espacio;
		Consola::MoverCursor(temp);
	}

	return (*mensajeFlotante).Mostrar();
}

void VentanaEntrada::CalcularTamano() {
	unsigned int largoMinimoX = 3;
	unsigned int largoMinimoY = 3;

	largoMinimoX = titulo.size() + 2;
	
	largoMinimoY += 3; //Le sumo 3 por la altura del cuadrado de entrada.

	if(mensajeFlotante->Largo() > largoMinimoX-2)
		largoMinimoX = mensajeFlotante->Largo()+2;

	for (unsigned int i = 0; i < mensajeAviso.size(); i++)
	{
		if (mensajeAviso[i].size() > largoMinimoX - 2)
			largoMinimoX = mensajeAviso[i].size() + 2;
	}

	largoMinimoY += mensajeAviso.size();

	tamanoVentana.X = largoMinimoX;
	tamanoVentana.Y = largoMinimoY;
}

VentanaDial::VentanaDial(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, Dial* _dial, COORD tamano) : Ventana(_titulo, posicion, fondo, texto, tamano) {
	//Separo el mensaje en varios strings, usando '\n' de separador, para poder dimensionar la ventana correctamente.
	if (mensaje.at(mensaje.size() - 1) != '\n')
		mensaje += "\n";
	string delimitador = "\n";
	size_t pos = 0;
	std::string token;
	while ((pos = mensaje.find(delimitador)) != string::npos) {
		token = mensaje.substr(0, pos);
		mensajeAviso.push_back(token);
		mensaje.erase(0, pos + delimitador.length());
	}

	dial = _dial;
}

int VentanaDial::DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, Dial* _dial, COORD tamano){
	VentanaDial temp(_titulo, posicion, fondo, texto, mensaje, _dial, tamano);
	if (tamano.X == 0 && tamano.Y == 0)
		temp.CalcularTamano();
	return temp.DibujarVentana();
}

int VentanaDial::DibujarVentana() {
	COORD posicionOriginal = Ventana::DibujarVentana();
	COORD nuevaPosicion = posicionOriginal;
	ReiniciarConsola rc; //Creo un objeto ReiniciarConsola que al salir de la función reiniciará los colores.

	//Cambio el color para dibujar la ventana.
	Consola::ColorTexto(colorTexto);
	Consola::ColorFondo(colorFondo);

	//Coloco el cursor en la posición correcta para empezar a escribir el mensaje.
	nuevaPosicion.Y = Consola::PosicionCursor().Y;
	nuevaPosicion.X = posicionOriginal.X;

	//Imprimo el mensaje.
	for (unsigned short int i = 0; i < mensajeAviso.size(); i++)
	{
		Consola::MoverCursor(nuevaPosicion);
		cout << mensajeAviso[i];
		nuevaPosicion.Y++;
	}

	//Agrego una tabulación variable para centrar el cuadro de entrada.
	SHORT temp = (SHORT)(mensajeAviso.size() + 1);
	Consola::MoverCursor({ posicionOriginal.X,  posicionOriginal.Y + temp });
	int espacio = (tamanoVentana.X - dial->Largo() - 2) / 2;

	if (espacio > 0) {
		COORD temp = Consola::PosicionCursor();
		temp.X += espacio;
		Consola::MoverCursor(temp);
	}

	return dial->Mostrar();
}

void VentanaDial::CalcularTamano() {
	unsigned int largoMinimoX = 3;
	unsigned int largoMinimoY = 3;

	largoMinimoX = titulo.size() + 2;

	largoMinimoY += 1; //Le sumo 1 por la altura del dial.

	if (dial->Largo() > largoMinimoX - 2)
		largoMinimoX = dial->Largo() + 2;

	for (unsigned int i = 0; i < mensajeAviso.size(); i++)
	{
		if (mensajeAviso[i].size() > largoMinimoX - 2)
			largoMinimoX = mensajeAviso[i].size() + 2;
	}

	largoMinimoY += mensajeAviso.size();

	tamanoVentana.X = largoMinimoX;
	tamanoVentana.Y = largoMinimoY;
}