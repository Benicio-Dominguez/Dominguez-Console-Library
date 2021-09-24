#include <fstream>
#include "Consola.h"
#include "ImagenAscii.h"

imagenAscii::imagenAscii(asciiPixel* _pixeles, COORD _tamano) {
	pixeles = _pixeles;
	tamano = _tamano;
	liberarMemoria = false; //Si la imagen fue creada por código, entonces la referencia a la que apunta _pixeles no fue pedida dinámicamente, y no hay que eliminarla.
}

imagenAscii::~imagenAscii() {
	if (liberarMemoria && pixeles != NULL) {
		delete[] pixeles;
	}
}

void imagenAscii::Mostrar() {
	COORD posicionInicial = Consola::PosicionCursor();
	for (SHORT i = 0; i < tamano.Y; i++)
	{
		SHORT temp = i;
		Consola::MoverCursor({ posicionInicial.X, posicionInicial.Y + temp });

		for (SHORT j = 0; j < tamano.X; j++)
		{
			Consola::ColorTexto(pixeles[(i * tamano.X) + j].colorTxt);
			Consola::ColorFondo(pixeles[(i * tamano.X) + j].colorFnd);
			cout << pixeles[(i * tamano.X) + j].caracter;
		}
	}
}
COORD imagenAscii::Tamano() {
	return tamano;
}

bool imagenAscii::GuardarArchivo(string direccion) {
	fstream archivo;
	archivo.open(direccion);
	if (archivo.is_open()) {
		
		//Guardo las dimensiones de la imagen.
		archivo.write(reinterpret_cast<const char*>(&tamano), sizeof(COORD));
		
		//Guardo los contenidos de la imagen.
		archivo.write(reinterpret_cast<const char*>(pixeles), sizeof(asciiPixel) * tamano.X * tamano.Y);
		
		archivo.close();
		return true;
	}
	return false;
}

bool imagenAscii::CargarArchivo(string direccion) {
	fstream archivo;
	archivo.open(direccion);
	if (archivo.is_open()) {
		COORD temp;
		
		//Cargo el tamaño de la imagen.
		archivo.read(reinterpret_cast<char*>(&temp), sizeof(COORD));
		if (pixeles != NULL)
			delete[] pixeles;

		//En función de ese tamaño, pido memoria que voy a liberar en el destructor, y cargo la información.
		pixeles = new asciiPixel[temp.X * temp.Y];
		archivo.read(reinterpret_cast<char*>(pixeles), sizeof(asciiPixel) * tamano.X * tamano.Y);
		liberarMemoria = true; //Pongo en true esta variable, para liberar la memoria recién pedida en el destructor.

		archivo.close();
		return true;
	}
	return false;
}

bool imagenAscii::InsertarPixel(COORD lugar, char caracter, colorConsola colorTexto, colorConsola colorFondo) {
	asciiPixel temp;
	temp.caracter = caracter;
	temp.colorFnd = colorFondo;
	temp.colorTxt = colorTexto;

	if (pixeles == NULL)
		return false;

	else if (lugar.X < tamano.X && lugar.Y < tamano.Y){
		pixeles[lugar.X + tamano.X * lugar.Y] = temp; //La fórmula rara es para pasar de arreglo a matriz.
		return true;
	}

	else
		return false;
}

asciiPixel imagenAscii::PixelEn(COORD lugar) {
	return pixeles[lugar.X + tamano.X * lugar.Y];
}