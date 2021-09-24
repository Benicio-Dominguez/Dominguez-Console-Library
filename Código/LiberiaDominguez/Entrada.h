#pragma once
#include <WinUser.h>

enum class tecla {
	//Los códigos de letra están en https://docs.microsoft.com/en-us/windows/win32/inputdev/virtual-key-codes (Para Windows)
	Vacio = 0,
	Enter = 0x0D,
	FlechaArriba = 0x26,
	FlechaAbajo = 0x28,
	FlechaIzquierda = 0x25,
	FlechaDerecha = 0x27,
	Espacio = 0x20,
	Shift = 0x10,
	Retroceso = 0x08,
	Tabulador = 0x09,
	F1 = 0x70,
	F2 = 0x71,
	F3 = 0x72,
	F4 = 0x73,
	F5 = 0x74,
	F6 = 0x75,
	F7 = 0x76,
	F8 = 0x77,
	F9 = 0x78,
	F10 = 0x79,
	F11 = 0x7A,
	F12 = 0x7B,
	_0 = 0x30,
	_1 = 0x31,
	_2 = 0x32,
	_3 = 0x33,
	_4 = 0x34,
	_5 = 0x35,
	_6 = 0x36,
	_7 = 0x37,
	_8 = 0x38,
	_9 = 0x39,
	A = 0x41,
	B = 0x42,
	C = 0x43,
	D = 0x44,
	E = 0x45,
	F = 0x46,
	G = 0x47,
	H = 0x48,
	I = 0x49,
	J = 0x4A,
	K = 0x4B,
	L = 0x4C,
	M = 0x4D,
	N = 0x4E,
	Ñ = 0xC0,
	O = 0x4F,
	P = 0x50,
	Q = 0x51,
	R = 0x52,
	S = 0x53,
	T = 0x54,
	U = 0x55,
	V = 0x56,
	W = 0x57,
	X = 0x58,
	Y = 0x59,
	Z = 0x5A,
	Coma = 0xBC,
	Punto = 0xBE,
	Guion = 0xBD,
	Suma = 0xBB,
	Acento = 0xDE
};
enum class estadoTecla {
	suelta,
	presionada,
	abajo
};
/// <summary>
/// Las 8 posibles direcciones a las que pueden apuntar las flechas direccionales.
/// </summary>
enum class direccionales {
	vacio,
	nada,
	arriba,
	arribaDerecha,
	derecha,
	abajoDerecha,
	abajo,
	abajoIzquierda,
	izquierda,
	arribaIzquierda
};

/// <summary>
/// Encapsula las funciones de entrada por teclado.
/// </summary>
class Entrada {
private:
public:
	/// <summary>
	/// Devuelve verdadero si la telcla especificada se encuentra presionada.
	/// </summary>
	static bool EstaAbajo(tecla entrada);

	/// <summary>
	/// Devuelve verdadero la primera vez que se presiona una tecla. Luego devuelve falso hasta que esta se suelta y se vuelve a presionar.
	/// </summary>
	static estadoTecla EstadoTecla(tecla entrada);

	/// <summary>
	/// Devuelve el estado actual de las flechas direccionales.
	/// </summary>
	static direccionales AbajoDireccionales();

	/// <summary>
	/// Devuelve el último botón presionado en las direccionales la primera vez que se presiona. Luego no lo devuelve más hasta que el usuario lo suelta, o presiona otro.
	/// </summary>
	static direccionales PresionoDireccionales();
	
	/// <summary>
	/// Devuelve el último botón presionado en el teclado.
	/// </summary>
	static tecla PresionoTeclado();
};
