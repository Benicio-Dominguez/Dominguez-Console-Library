//Librería para colorear la consola de windows, por Benicio Dominguez

#include<Windows.h>
#include<iostream>
#include"Consola.h"

using namespace std;

COORD Consola::tamanoConsola;
colorConsola Consola::colorFondoConsola;
colorConsola Consola::colorGrabadoConsola;
char Consola::caracterFondo;
colorConsola Consola::colorTextoActual;
colorConsola Consola::colorFondoActual;

WORD Consola::ColorWORD(colorConsola color, bool fondo) {
	WORD colorFinal = 0;
	switch (color)
	{
	case colorConsola::negro:
		colorFinal = 0;
		break;
	case colorConsola::azulOscuro:
		colorFinal = BACKGROUND_BLUE;
		break;
	case colorConsola::verdeOscuro:
		colorFinal = BACKGROUND_GREEN;
		break;
	case colorConsola::cianOscuro:
		colorFinal = BACKGROUND_GREEN | BACKGROUND_BLUE;
		break;
	case colorConsola::rojoOscuro:
		colorFinal = BACKGROUND_RED;
		break;
	case colorConsola::magentaOscuro:
		colorFinal = BACKGROUND_BLUE | BACKGROUND_RED;
		break;
	case colorConsola::amarilloOscuro:
		colorFinal = BACKGROUND_RED | BACKGROUND_GREEN;
		break;
	case colorConsola::gris:
		colorFinal = BACKGROUND_INTENSITY;
		break;
	case colorConsola::grisOscuro:
		colorFinal = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
		break;
	case colorConsola::azul:
		colorFinal = BACKGROUND_BLUE | BACKGROUND_INTENSITY;
		break;
	case colorConsola::verde:
		colorFinal = BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case colorConsola::cian:
		colorFinal = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case colorConsola::rojo:
		colorFinal = BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case colorConsola::magenta:
		colorFinal = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_INTENSITY;
		break;
	case colorConsola::amarillo:
		colorFinal = BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	case colorConsola::blanco:
		colorFinal = BACKGROUND_BLUE | BACKGROUND_RED | BACKGROUND_GREEN | BACKGROUND_INTENSITY;
		break;
	}

	if (!fondo)
		colorFinal = colorFinal >> 4; //El valor binario actual está puesto para el fondo. 
		//Si quiero el valor para el frente (El texto), tengo que desplazar los bits 4 espacios a la derecha.

	return colorFinal;
}

void Consola::ColorTexto(colorConsola color) {
	colorTextoActual = color;
	CONSOLE_SCREEN_BUFFER_INFO colorActual;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &colorActual);
	colorActual.wAttributes = colorActual.wAttributes & 0b11110000; //Borro el color de texto.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorWORD(color, false) | colorActual.wAttributes);
	//Vuelvo a setear el color de la consola, pero solo el texto, manteniendo el color de fondo actual.
}
void Consola::ColorFondo(colorConsola color) {
	colorFondoActual = color;
	CONSOLE_SCREEN_BUFFER_INFO colorActual;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &colorActual);
	colorActual.wAttributes = colorActual.wAttributes & 0b00001111; //Borro el color de fondo.
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ColorWORD(color, true) | colorActual.wAttributes);
	//Vuelvo a setear el color de la consola, pero solo el fondo, manteniendo el color de texto actual.
}
void Consola::LimpiarColor() {
	ColorTexto(colorConsola::blanco);
	ColorFondo(colorConsola::negro);
}
void Consola::MoverCursor(COORD destino) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), destino);
}
COORD Consola::PosicionCursor() {
	CONSOLE_SCREEN_BUFFER_INFO infoConsola;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &infoConsola);
	return infoConsola.dwCursorPosition;
}
void Consola::ImprimirFondo() {
	CONSOLE_SCREEN_BUFFER_INFO formatoActual;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &formatoActual);
	COORD origen{ 0,0 };
	MoverCursor(origen);
	ColorFondo(colorFondoConsola);
	ColorTexto(colorGrabadoConsola);

	for (int i = 0; i < tamanoConsola.X; i++)
	{
		for (int j = 0; j < tamanoConsola.Y; j++)
		{
			cout << caracterFondo;
		}
		cout << endl;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), formatoActual.wAttributes);
}
void Consola::ConfigurarFondo(colorConsola fondo, colorConsola grabado, char caracter, COORD tamano) {
	tamanoConsola = tamano;
	caracterFondo = caracter;
	colorFondoConsola = fondo;
	colorGrabadoConsola = grabado;
}

colorConsola Consola::ColorTextoActual() {
	return colorTextoActual;
}
colorConsola Consola::ColorFondoActual() {
	return colorFondoActual;
}

void Consola::BajarCursor(SHORT posX = PosicionCursor().X) {
	MoverCursor({ posX, PosicionCursor().Y + 1});
}

ReiniciarConsola::ReiniciarConsola() {
	coutHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(coutHandle, &colorOriginal);
}
ReiniciarConsola::~ReiniciarConsola() {
	SetConsoleTextAttribute(coutHandle, colorOriginal.wAttributes);
}