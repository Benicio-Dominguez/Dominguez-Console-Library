#pragma once
#include "Consola.h"
#include "Widget.h"

struct asciiPixel {
	char caracter = ' ';
	colorConsola colorTxt = colorConsola::blanco;
	colorConsola colorFnd = colorConsola::negro;
};

class imagenAscii{
private:
	COORD tamano;
	asciiPixel* pixeles;
	bool liberarMemoria; //Determina si pixeles será o no eliminado en el destructor, para evitar una violación de acceso a la memoria.
public:
	/// <summary>
	/// Crea una nueva imagen ascii a partir de un arreglo de pixeles.
	/// </summary>
	/// <param name="_pixeles">Arreglo de pixeles para crear una nueva imagen.</param>
	/// <param name="_tamano">El tamaño en caracteres de la imagen.</param>
	imagenAscii(asciiPixel * _pixeles, COORD _tamano);
	/// <summary>
	/// Carga una imagen ascii desde el disco duro.
	/// </summary>
	/// <param name="direccion">La direccion del archivo a cargar.</param>
	imagenAscii(string direccion);
	~imagenAscii();
	/// <summary>
	/// Imprime la imagen en una posici¢n dada.
	/// </summary>
	void Mostrar();
	/// <summary>
	/// Devuelve un registro COORD que contiene el tamaño X e Y de la imagen.
	/// </summary>
	COORD Tamano();
	bool InsertarPixel(COORD lugar, char caracter, colorConsola colorTexto = colorConsola::blanco, colorConsola colorFondo = colorConsola::negro);
	/// <summary>
	/// Devuelve el pixel en "lugar".
	/// </summary>
	asciiPixel PixelEn(COORD lugar);
	bool GuardarArchivo(string direccion);
	bool CargarArchivo(string direccion);
};
