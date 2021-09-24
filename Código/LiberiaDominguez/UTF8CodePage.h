#pragma once
#include <iostream>
#include <Windows.h>
/// <summary>
/// Al instanciar un objeto de esta clase la consola se pone en modo UTF-8. Al finalizar el programa se deja como estaba antes.
/// </summary>
class UTF8CodePage {
public:
    UTF8CodePage() : paginaDeCodigosAntigua(GetConsoleOutputCP()) {
        //En el constructor pongo la p�gina de c�digos UTF-8.
        //Tambi�n guardo la p�gina de c�digos actual.
        SetConsoleOutputCP(CP_UTF8);
    }
    ~UTF8CodePage() {
        //En el destructor dejo la p�gina de c�digos que estaba.
        SetConsoleOutputCP(paginaDeCodigosAntigua);
    }

private:
    unsigned int paginaDeCodigosAntigua;
};
