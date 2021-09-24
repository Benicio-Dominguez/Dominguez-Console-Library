#pragma once
#include <Windows.h>
/// <summary>
/// Módulo es una interfaz que permite que las clases que la implementen puedan ser agregados como widgets a las ventanas.
/// </summary>
class Widget {
protected:
	//Posición del widget relativo al origen de la ventana.
	COORD posicion;
public:
	//Metodo virtual para mostrar el widget
	virtual void Mostrar() = 0;
};