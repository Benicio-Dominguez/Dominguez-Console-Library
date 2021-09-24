#pragma once
#include <iostream>
#include <Windows.h>
/// <summary>
/// Al instanciar un objeto de esta clase la consola se pone en modo OEM858. Al finalizar el programa se deja como estaba antes.
/// </summary>
class OEM858CodePage {
public:
    OEM858CodePage() : paginaDeCodigosAntigua(GetConsoleOutputCP()) {
        //En el constructor pongo la p�gina de c�digos UTF-8.
        //Tambi�n guardo la p�gina de c�digos actual.
        SetConsoleOutputCP(858);
    }
    ~OEM858CodePage() {
        //En el destructor dejo la p�gina de c�digos que estaba.
        SetConsoleOutputCP(paginaDeCodigosAntigua);
    }

private:
    unsigned int paginaDeCodigosAntigua;
};
