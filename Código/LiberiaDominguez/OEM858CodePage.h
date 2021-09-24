#pragma once
#include <iostream>
#include <Windows.h>
/// <summary>
/// Al instanciar un objeto de esta clase la consola se pone en modo OEM858. Al finalizar el programa se deja como estaba antes.
/// </summary>
class OEM858CodePage {
public:
    OEM858CodePage() : paginaDeCodigosAntigua(GetConsoleOutputCP()) {
        //En el constructor pongo la página de códigos UTF-8.
        //También guardo la página de códigos actual.
        SetConsoleOutputCP(858);
    }
    ~OEM858CodePage() {
        //En el destructor dejo la página de códigos que estaba.
        SetConsoleOutputCP(paginaDeCodigosAntigua);
    }

private:
    unsigned int paginaDeCodigosAntigua;
};
