#include "Formato.h"
#include <string>
#include<iostream>
#include<Windows.h>
#include "Entrada.h"
#include "Consola.h"
#include "Utilidades.h"
#include "Ventana.h"
using namespace std;

void Formato::MaquinaEscribir(string mensaje, velocidadTexto velocidad) {
	for (size_t i = 0; i < mensaje.size(); i++)
	{
		cout << mensaje.at(i);
		Sleep((DWORD)velocidad);
	}
}

unsigned int Formato::Menu(string* mensajes, unsigned int cantidadElementos, bool liberarMemoria, unsigned int indice) {
	CONSOLE_SCREEN_BUFFER_INFO infoConsola;
	COORD nuevaPosicion;
	COORD primeraPosicion;
	HANDLE coutHandle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(coutHandle, &infoConsola);
	primeraPosicion = infoConsola.dwCursorPosition;

	//Imprimo el título y todas las opciones.
	cout << mensajes[0] << endl;
	for (unsigned int i = 1; i < cantidadElementos; i++)
	{
		nuevaPosicion = primeraPosicion;
		nuevaPosicion.X += 4;
		nuevaPosicion.Y += (i);
		SetConsoleCursorPosition(coutHandle, nuevaPosicion);
		cout << mensajes[i] << ".\n";
	}

	//Imprimo el cursor por primera vez.
	nuevaPosicion = primeraPosicion;
	nuevaPosicion.Y += indice;
	nuevaPosicion.X = primeraPosicion.X + 3;
	SetConsoleCursorPosition(coutHandle, nuevaPosicion);
	cout << ">";

	//En este bucle leo la entrada y muevo el cursor, hasta que toco enter.
	while (Entrada::EstadoTecla(tecla::Enter) != estadoTecla::presionada) {
		direccionales entrada = Entrada::PresionoDireccionales();
		if (entrada == direccionales::arriba) {
			if (indice > 1)
				indice--;
			else
				indice = cantidadElementos - 1;

			nuevaPosicion.X = primeraPosicion.X + 3;
			SetConsoleCursorPosition(coutHandle, nuevaPosicion);
			cout << " ";

			nuevaPosicion = primeraPosicion;
			nuevaPosicion.Y += indice;
			nuevaPosicion.X = primeraPosicion.X + 3;
			SetConsoleCursorPosition(coutHandle, nuevaPosicion);
			cout << ">";
		}
		if (entrada == direccionales::abajo)
		{
			if (indice < cantidadElementos - 1)
				indice++;
			else
				indice = 1;

			nuevaPosicion.X = primeraPosicion.X + 3;
			SetConsoleCursorPosition(coutHandle, nuevaPosicion);
			cout << " ";

			nuevaPosicion = primeraPosicion;
			nuevaPosicion.Y += indice;
			nuevaPosicion.X = primeraPosicion.X + 3;
			SetConsoleCursorPosition(coutHandle, nuevaPosicion);
			cout << ">";
		}

	}
	//Coloco el cursor debajo del menú.
	nuevaPosicion = primeraPosicion;
	nuevaPosicion.Y += cantidadElementos;
	nuevaPosicion.X = 0;
	SetConsoleCursorPosition(coutHandle, nuevaPosicion);

	if (liberarMemoria)
		delete[] mensajes;

	return indice;
}

signed int Formato::Dial(int valorMinimo, int valorMaximo, bool permitirAumentoDeADiez) {
	//Calculo la cantidad de dígitos en valorMaximo
	int cantDigitsValMax = cantdigitos(valorMaximo);

	//Inicializo el valor elegido.
	int valorElegido = valorMinimo;

	COORD posicionInicial = Consola::PosicionCursor();
	
	cout << "<";
	//Imprimo ceros para compenzar la diferencia entre el valor actual y el máximo.
	for (unsigned int i = 0; i < cantDigitsValMax - cantdigitos(valorElegido); i++)
	{
		cout << "0";
	}
	cout << valorElegido << ">";

	do{
		bool imprimir = false;
		direccionales entrada = Entrada::PresionoDireccionales();
		if (entrada == direccionales::derecha)
		{
			valorElegido++;
			if (valorElegido > valorMaximo)
				valorElegido = valorMinimo;
			imprimir = true;
		}
		else if (entrada == direccionales::izquierda)
		{
			valorElegido--;
			if (valorElegido < valorMinimo)
				valorElegido = valorMaximo;
			imprimir = true;
		}
		else if (entrada == direccionales::arriba)
		{
			if(permitirAumentoDeADiez)
				valorElegido+=10;
			else
				valorElegido ++;
			if (valorElegido > valorMaximo)
				valorElegido = valorMinimo;
			imprimir = true;
		}
		else if (entrada == direccionales::abajo)
		{
			if (permitirAumentoDeADiez)
				valorElegido -= 10;
			else
				valorElegido--;
			if (valorElegido < valorMinimo)
				valorElegido = valorMaximo;
			imprimir = true;
		}
		if (imprimir)
		{
			Consola::MoverCursor(posicionInicial);
			cout << "<";
			//Imprimo ceros para compenzar la diferencia entre el valor actual y el máximo.
			for (unsigned int i = 0; i < cantDigitsValMax - cantdigitos(valorElegido); i++)
			{
				cout << "0";
			}
			cout << valorElegido << ">";
		}
	} while (Entrada::EstadoTecla(tecla::Enter) != estadoTecla::presionada);
	return valorElegido;
}

string Formato::EntradaTexto(unsigned int tamanoLinea, unsigned int tamanoEntrada, string valorInicial) {
	
	while (Entrada::EstaAbajo(tecla::Enter)); //Me enclavo hasta que el usuario suelte el enter.

	COORD posicionInicial = Consola::PosicionCursor();
	COORD posicionTexto;
	string salida = valorInicial;

	//Imprimo la parte de arriba del cuadro.
	cout << Ventana::simple.esquinaSupIzquierda;
	for (unsigned short int i = 0; i < tamanoLinea; i++)
	{
		cout << Ventana::simple.horizontal;
	}
	cout << Ventana::simple.esquinaSupDerecha;

	//Imprimo el centro del cuadro.
	Consola::BajarCursor(posicionInicial.X);
	cout << Ventana::simple.vertical;
	posicionTexto = Consola::PosicionCursor(); //Guardo la posicion desde la que debo ingresar el texto.
	cout << salida;
	for (unsigned short int i = 0; i < tamanoLinea-salida.size(); i++)
	{
		cout << Ventana::simple.relleno;
	}
	cout << Ventana::simple.vertical;

	//Imprimo la base del cuadro.
	Consola::BajarCursor(posicionInicial.X);
	cout << Ventana::simple.esquinaInfIzquierda;
	for (unsigned short int i = 0; i < tamanoLinea; i++)
	{
		cout << Ventana::simple.horizontal;
	}
	cout << Ventana::simple.esquinaInfDerecha;

	Consola::MoverCursor({ posicionTexto.X + (SHORT)salida.size(),posicionTexto.Y });

	bool acento = false;
	//Modifico el string y lo reimprimo hasta que el usuario toca enter.
	do {
		bool shiftPresionado = Entrada::EstaAbajo(tecla::Shift);

		tecla entrada = Entrada::PresionoTeclado();
		bool imprimir = true;
		
		switch (entrada)
		{
		case tecla::Vacio:
			imprimir = false;
			break;
		case tecla::Espacio:
			if(salida.size()<tamanoEntrada) 
				salida.push_back(' ');
			break;
		case tecla::Retroceso:
			if (acento)
				acento = false;
			else if (salida.size() > 0) {
				salida.pop_back();
			}
			break;
		case tecla::_0:
			if (salida.size() < tamanoEntrada)
				salida.push_back('0');
			break;
		case tecla::_1:
			if (salida.size() < tamanoEntrada)
				salida.push_back('1');
			break;
		case tecla::_2:
			if (salida.size() < tamanoEntrada)
				salida.push_back('2');
			break;
		case tecla::_3:
			if (salida.size() < tamanoEntrada)
				salida.push_back('3');
			break;
		case tecla::_4:
			if (salida.size() < tamanoEntrada)
				salida.push_back('4');
			break;
		case tecla::_5:
			if (salida.size() < tamanoEntrada)
				salida.push_back('5');
			break;
		case tecla::_6:
			if (salida.size() < tamanoEntrada)
				salida.push_back('6');
			break;
		case tecla::_7:
			if (salida.size() < tamanoEntrada)
				salida.push_back('7');
			break;
		case tecla::_8:
			if (salida.size() < tamanoEntrada)
				salida.push_back('8');
			break;
		case tecla::_9:
			if (salida.size() < tamanoEntrada)
				salida.push_back('9');
			break;
		case tecla::A:
			if (salida.size() < tamanoEntrada) {
				if (acento) {
					if (shiftPresionado)
						salida.push_back('µ');
					else
						salida.push_back(' ');
					acento = false;
				}
				else {
					if (shiftPresionado)
						salida.push_back('A');
					else
						salida.push_back('a');
				}
			}
			break;
		case tecla::B:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('B');
				else
					salida.push_back('b');
			}
			break;
		case tecla::C:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('C');
				else
					salida.push_back('c');
			}
			break;
		case tecla::D:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('D');
				else
					salida.push_back('d');
			}
			break;
		case tecla::E:
			if (salida.size() < tamanoEntrada) {
				if (acento) {
					if (shiftPresionado)
						salida.push_back('');
					else
						salida.push_back('‚');
					acento = false;
				}
				else {
					if (shiftPresionado)
						salida.push_back('E');
					else
						salida.push_back('e');
				}
			}
			break;
		case tecla::F:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('F');
				else
					salida.push_back('f');
			}
			break;
		case tecla::G:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('G');
				else
					salida.push_back('g');
			}
			break;
		case tecla::H:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('H');
				else
					salida.push_back('h');
			}
			break;
		case tecla::I:
			if (salida.size() < tamanoEntrada) {
				if (acento) {
					if (shiftPresionado)
						salida.push_back('Ö');
					else
						salida.push_back('¡');
					acento = false;
				}
				else {
					if (shiftPresionado)
						salida.push_back('I');
					else
						salida.push_back('i');
				}
			}
			break;
		case tecla::J:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('J');
				else
					salida.push_back('j');
			}
			break;
		case tecla::K:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('K');
				else
					salida.push_back('k');
			}
			break;
		case tecla::L:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('L');
				else
					salida.push_back('l');
			}
			break;
		case tecla::M:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('M');
				else
					salida.push_back('m');
			}
			break;
		case tecla::N:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('N');
				else
					salida.push_back('n');
			}
			break;
		case tecla::Ñ:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('¥');
				else
					salida.push_back('¤');
			}
			break;
		case tecla::O:
			if (salida.size() < tamanoEntrada) {
				if (acento) {
					if (shiftPresionado)
						salida.push_back('à');
					else
						salida.push_back('¢');
					acento = false;
				}
				else {
					if (shiftPresionado)
						salida.push_back('O');
					else
						salida.push_back('o');
				}
			}
			break;
		case tecla::P:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('P');
				else
					salida.push_back('p');
			}
			break;
		case tecla::Q:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('Q');
				else
					salida.push_back('q');
			}
			break;
		case tecla::R:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('R');
				else
					salida.push_back('r');
			}
			break;
		case tecla::S:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('S');
				else
					salida.push_back('s');
			}
			break;
		case tecla::T:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('T');
				else
					salida.push_back('t');
			}
			break;
		case tecla::U:
			if (salida.size() < tamanoEntrada) {
				if (acento) {
					if (shiftPresionado)
						salida.push_back('é');
					else
						salida.push_back('£');
					acento = false;
				}
				else {
					if (shiftPresionado)
						salida.push_back('U');
					else
						salida.push_back('u');
				}
			}
			break;
		case tecla::V:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('V');
				else
					salida.push_back('v');
			}
			break;
		case tecla::W:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('W');
				else
					salida.push_back('w');
			}
			break;
		case tecla::X:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('X');
				else
					salida.push_back('x');
			}
			break;
		case tecla::Y:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('Y');
				else
					salida.push_back('y');
			}
			break;
		case tecla::Z:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('Z');
				else
					salida.push_back('z');
			}
			break;
		case tecla::Punto:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back(':');
				else
					salida.push_back('.');
			}
			break;
		case tecla::Coma:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back(';');
				else
					salida.push_back(',');
			}
			break;
		case tecla::Guion:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('_');
				else
					salida.push_back('-');
			}
			break;
		case tecla::Suma:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('*');
				else
					salida.push_back('+');
			}
			break;
		case tecla::Acento:
			if (salida.size() < tamanoEntrada) {
				if (shiftPresionado)
					salida.push_back('ù');
				else {
					acento = true;
					imprimir = false;
				}
			}
			break;
		default:
			imprimir = false;
			break;
		}

		if (imprimir) {
			Consola::MoverCursor(posicionTexto);
			if (salida.size() <= tamanoLinea){
				cout << salida;
				for (size_t i = 0; i < tamanoLinea-salida.size(); i++)
				{
					cout << ' ';
				}
				Consola::MoverCursor({ posicionTexto.X + (SHORT)salida.size(),posicionTexto.Y });
			}
			else
			{
				for (size_t i = salida.size() - tamanoLinea; i < salida.size(); i++)
				{
					cout << salida.at(i);
				}
				Consola::MoverCursor({ posicionTexto.X + (SHORT)tamanoLinea - 1,posicionTexto.Y });
			}
		}

	} while (Entrada::EstadoTecla(tecla::Enter) != estadoTecla::presionada);
	return salida;
}

void Formato::TextoFlotante(string mensaje) {
	COORD nuevaPosicion = Consola::PosicionCursor();
	for (size_t i = 0; i < mensaje.size(); i++)
	{
		if (mensaje[i] == '\n')
			Consola::BajarCursor(nuevaPosicion.X);
		else
			cout << mensaje[i];
	}
};

Menu::Menu(string* _mensajes, unsigned int _cantidadElementos) {
	mensajes = _mensajes;
	cantidadElementos = _cantidadElementos;
}

Menu::~Menu() {
	//Libero la memoria que ocupaban los mensajes.
	if(mensajes != NULL)
		delete[] mensajes;
}

unsigned int Menu::Mostrar(bool reiniciarIndice) {
	//Guardo el resultado en indice, para que la proxima vez que se abra el menú el cursor esté en la ultima posición elegida.
	if (reiniciarIndice)
		indice = 1;
	return (indice = Formato::Menu(mensajes, cantidadElementos, false, indice));
}

int Menu::CantidadElementos() {
	return cantidadElementos;
}

int Menu::LargoDe(int elemento) {
	if (elemento < cantidadElementos && elemento >= 0)
		return mensajes[elemento].size();
	else
		return -1;
}

Dial::Dial(int vMax, int vMin, bool _aumentoDeADiez){
	valorMax = vMax;
	valorMin = vMin;
	aumentoDeADiez = _aumentoDeADiez;
}

int Dial::Mostrar() {
	return Formato::Dial(valorMin, valorMax, aumentoDeADiez);
}

unsigned int Dial::Largo() {
	return cantdigitos(valorMax) + 2;//Se suma dos, porque el dial siempre tiene los símbolos "<" y ">".
}