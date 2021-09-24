#pragma once

#include <iostream>
#include <windows.h>
#include <vector>
#include "Consola.h"
#include "ImagenAscii.h"
#include "Formato.h"
using namespace std;

struct graficosCuadro {
	//������������������
	char vertical = '�',
		horizontal = '�',
		esquinaSupDerecha = '�',
		esquinaSupIzquierda = '�',
		esquinaInfIzquierda = '�',
		esquinaInfDerecha = '�',
		relleno = ' ';
};
/// <summary>
/// Representa una ventana dentro de la aplicaci�n. Contiene todas sus propiedades, y funciones para su manejo y utilizaci�n.
/// </summary>
class Ventana {
protected:
	COORD posicionVentana;
	COORD tamanoVentana;
	string titulo;
	colorConsola colorFondo;
	colorConsola colorTexto;
	graficosCuadro graficos = doble;
public:
	const static graficosCuadro simple;
	const static graficosCuadro doble;

	/// <summary>
	/// Constructor para una ventana gen�rica.
	/// </summary>
	Ventana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, COORD tamano = { 0,0 });
	static COORD DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, COORD tamano = { 0,0 });
	/// <summary>
	/// Dibuja la ventana seg�n las propiedades establecidas y coloca el cursor adentro.
	/// </summary>
	/// <returns>La ubicaci�n del cursor dentro de la ventana.</returns>
	COORD DibujarVentana();
	void MoverVentana(COORD nuevaPosicion);
	void CambiarTamano(COORD nuevoTamano);
	void CalcularTamano();
	/// <summary>
	/// Cambia los gr�ficos con los que se va a dibujar la ventana.
	/// </summary>
	void CambiarGraficos(graficosCuadro graficosNuevos);
};

class VentanaMensaje : public Ventana {
protected:
	vector<string> mensajeAviso;
	string mensajeAceptar;
	imagenAscii* imagen = NULL;
public:
	VentanaMensaje(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, string aceptar, COORD tamano = { 0,0 }, imagenAscii* _imagen = NULL);
	static COORD DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, string aceptar, COORD tamano = { 0,0 }, imagenAscii* _imagen = NULL);
	COORD DibujarVentana();
	void CalcularTamano();
	void CambiarMensaje(string mensaje);
};

/// <summary>
/// Representa una ventana que contiene un men� de opciones m�ltiples.
/// </summary>
class VentanaMenu : public Ventana{
private:
	Menu *menu;
	imagenAscii* imagen = NULL;
public:
	/// <summary>
	/// Crea una ventana con men�.
	/// </summary>
	/// <param name="_menu">Una referencia a un men�.</param>
	VentanaMenu(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, Menu* _menu, COORD tamano = { 0,0 }, imagenAscii* _imagen = NULL);
	/// <summary>
	/// Dibuja una ventana con un men� de opciones m�ltiples sin necesidad de crear un objeto.
	/// </summary>
	/// <returns>La opci�n elegida por el usuario</returns>
	static unsigned int DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, Menu* _menu, COORD tamano = { 0,0 }, imagenAscii* _imagen = NULL);
	/// <summary>
	/// Dibuja una ventana con un men�.
	/// </summary>
	/// <returns>El �ndice de la opci�n elegida</returns>
	unsigned int DibujarVentana();
	/// <summary>
	/// Calcula el tama�o m�nimo para la ventana en funci�n de su contenido.
	/// </summary>
	void CalcularTamano();
};

class VentanaEntrada : public Ventana {
private:
	CuadroEntrada *mensajeFlotante;
	vector<string> mensajeAviso;
public:
	VentanaEntrada(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, CuadroEntrada* _mensajeFlotante, COORD tamano = { 0,0 });
	static string DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, CuadroEntrada* _mensajeFlotante, COORD tamano = { 0,0 });
	/// <summary>
	/// Dibuja la ventana y devuelve el string ingresado por el usuario.
	/// </summary>
	string DibujarVentana();
	void CalcularTamano();
};

class VentanaDial : public Ventana {
private:
	vector<string> mensajeAviso;
	Dial* dial;
public:
	VentanaDial(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, Dial* _dial, COORD tamano = { 0,0 });
	static int DibujarVentana(string _titulo, COORD posicion, colorConsola fondo, colorConsola texto, string mensaje, Dial* _dial, COORD tamano = { 0,0 });
	/// <summary>
	/// Dibuja la ventana y devuelve el n�mero ingresado por el usuario.
	/// </summary>
	int DibujarVentana();
	void CalcularTamano();
};

