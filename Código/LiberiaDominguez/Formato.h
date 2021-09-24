#pragma once

#include <string>
#include<iostream>
#include<Windows.h>
#include "Entrada.h"
using namespace std;

enum class velocidadTexto {
	lento = 100,
	medio = 50,
	rapido = 20
};

class Formato {
private:
	static void ImprCharDesdeTecla(tecla teclaPresionada, bool shift = false);
public:
	/// <summary>
	/// Imprime caracter por caracter un mensaje.
	/// </summary>
	/// <param name="mensaje">El string del mensaje.</param>
	/// <param name="velocidad">Puede ser lento, medio o rapido.</param>
	static void MaquinaEscribir(string mensaje, velocidadTexto velocidad);

	/// <summary>
	/// Imprime una lista de elementos con formato. El primer elemento se toma como t�tulo. Permite al usuario elegir una opci�n, y devuelve su �ndice.
	/// </summary>
	/// <param name="mensajes">: Debe ser una lista enviada con el operador new, para poder liberar la memoria.</param>
	/// <param name="cantidadElementos">: Cantidad de elementos en el arreglo.</param>
	/// <returns>El n�mero de la opci�n seleccionada.</returns>
	static unsigned int Menu(string* mensajes, unsigned int cantidadElementos, bool liberarMemoria = true, unsigned int indice = 1);

	/// <summary>
	/// Espera a que el usuario ingrese un n�mero entre los valores m�nimo y m�ximo, usando las flechas. Devuelve el valor elegido. (^ = +1 ; v = -1; =� = +10; �= = -10)
	/// </summary>
	/// <param name="valorMin">Valor m�s bajo que puede adoptar la entrada.</param>
	/// <param name="valorMax">Valor m�s alto que puede adoptar la entrada.</param>
	/// <param name="permitirAumentoDeAdiez">Si es verdadero, permite que el usuario aumente el valor de diez en diez usando las flechas verticales.</param>
	/// <returns>El valor elegido.</returns>
	static signed int Dial(int valorMin, int valorMax, bool permitirAumentoDeADiez = false);

	/// <summary>
	/// Toma una entrada de texto del teclado dentro de un espacio reducido. Una vez superado el espacio se puede hacer scroll por el mensaje con las flechas direccionales. 
	/// </summary>
	/// <param name="tamanoLinea">Cantidad de caracteres que se pueden ingresar antes de que sea necesario hacer scroll.</param>
	/// <param name="tamanoEntrada">El largo m�ximo del string.</param>
	/// <returns>El string ingresado.</returns>
	static string EntradaTexto(unsigned int tamanoLinea, unsigned int tamanoEntrada, string valorInicial = "");

	/// <summary>
	/// Similar a un cout, pero con la sutil diferencia de que al imprimir un "\n" el cursor de la consola baja una l�nea desde la posici�n X donde se empez� a escribir, y no sobreescribe con espacios vac�os la distancia con el borde de la ventana.
	/// </summary>
	static void TextoFlotante(string mensaje);

};

/// <summary>
/// Representa un men� de opciones m�ltiples.
/// </summary>
class Menu{
private:
	string* mensajes; //Es un puntero para que al declarar el men� en el c�digo no sea necesario enviar una variable.
	int cantidadElementos;
	unsigned int indice = 1;
public:
	Menu(string* _mensajes, unsigned int _cantidadElementos);
	~Menu();
	
	/// <summary>
	/// Imprimo el men� y devuelvo la opci�n elegida.
	/// </summary>
	/// <returns>El �ndice de la opci�n elegida.</returns>
	unsigned int Mostrar(bool reiniciarIndice = false);
	
	/// <summary>
	/// Devuelve la cantidad de elementos del men�.
	/// </summary>
	int CantidadElementos();

	/// <summary>
	/// Devuelve la longitud de una opci�n del men�. Si el indice de opci�n no existe, devuelve -1.
	/// </summary>
	/// <param name="elemento">N�mero de elemento cuya longitud se desea conocer</param>
	/// <returns>El largo del elemento del men� pedido.</returns>
	int LargoDe(int elemento);
};

class CuadroEntrada{
private:
	string mensajeInicial;
	int longitudMaxima;
	int largo;
public:
	CuadroEntrada(int _largo, int _longitudMaxima, string _mensajeInicial = "") {
		largo = _largo;
		longitudMaxima = _longitudMaxima;
		mensajeInicial = mensajeInicial;
	}
	string Mostrar() {
		return Formato::EntradaTexto(largo, longitudMaxima, mensajeInicial);
	}
	int Largo() {
		return largo+2;
	}
};

class Dial {
private:
	int valorMax;
	int valorMin;
	bool aumentoDeADiez;
public:
	/// <summary>
	/// Crea un objeto del tipo dial con todas las configuraciones determinadas.
	/// </summary>
	/// <param name="vMax">Valor m�ximo que puede adoptar el dial.</param>
	/// <param name="vMin">Valor m�nimo que puede adoptar el dial.</param>
	/// <param name="aumentoDeADiez">Permite que el usuario aumente de a diez la cuenta con las flechas verticales.</param>
	Dial(int vMax, int vMin, bool _aumentoDeADiez);
	int Mostrar();
	unsigned int Largo();
};