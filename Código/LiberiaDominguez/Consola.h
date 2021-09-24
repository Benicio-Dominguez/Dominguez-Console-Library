#pragma once

#include<Windows.h>
#include<iostream>
using namespace std;

enum class colorConsola {
	negro,
	azulOscuro,
	verdeOscuro,
	cianOscuro,
	rojoOscuro,
	magentaOscuro,
	amarilloOscuro,
	gris,
	grisOscuro,
	azul,
	verde,
	cian,
	rojo,
	magenta,
	amarillo,
	blanco
};

/// <summary>
/// Encapsula las funciones de coloreado de la consola. Solo compatible con Windows. 
/// </summary>
class Consola {
	/*Esta clase encapsula el procedimiento para cambiar el color de los elementos de la consola.
	Esto se hace así para facilitar la portabilidad del programa, ya que si hubiera que cambiar la forma
	en la que la consola cambia los colores para llevar el programa a linux, solo hay que modificar
	el código acá, y no en todo el programa. Hecha por Benicio Dominguez.*/

private:
	/// <summary>
	/// Convierte un valor de tipo 'colorConsola' a tipo 'WORD'
	/// </summary>
	/// <param name="color"></param>
	/// <param name="fondo"></param>
	/// <returns></returns>
	static WORD ColorWORD(colorConsola color, bool fondo);
	static COORD tamanoConsola;
	static colorConsola colorFondoConsola;
	static colorConsola colorGrabadoConsola;
	static char caracterFondo;
	static colorConsola colorTextoActual;
	static colorConsola colorFondoActual;
public:
	/// <summary>
	/// Cambia el color del texto de la consola.
	/// </summary>
	static void ColorTexto(colorConsola color);

	/// <summary>
	/// Cambia el color del fondo de la consola.
	/// </summary>
	static void ColorFondo(colorConsola color);

	/// <summary>
	/// Deja la consola con fondo negro y texto blanco.
	/// </summary>
	static void LimpiarColor();

	/// <summary>
	/// Coloca el cursor de la consola en cierta coordenada. (ú= X =ú  v Y ^)
	/// </summary>
	static void MoverCursor(COORD destino);

	/// <summary>
	/// Baja el cursor una linea. Si se desea se puede manipular la posición X del cursor con posX. Devuelve la posición final del cursor.
	/// </summary>
	static void BajarCursor(SHORT posX);
	static COORD PosicionCursor();
	static void ImprimirFondo();
	static void ConfigurarFondo(colorConsola fondo, colorConsola grabado, char caracter, COORD tamano);
	static colorConsola ColorTextoActual();
	static colorConsola ColorFondoActual();
};

/// <summary>
/// Cuando es creado guarda la configuración actual de la consola, y cuando termina el programa la devuelve a su configuración original.
/// </summary>
class ReiniciarConsola {
private:
	CONSOLE_SCREEN_BUFFER_INFO colorOriginal;
public:
	HANDLE coutHandle;
	ReiniciarConsola();
	~ReiniciarConsola();
};