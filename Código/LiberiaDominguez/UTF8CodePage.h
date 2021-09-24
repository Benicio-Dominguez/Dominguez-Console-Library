#pragma once
#include <iostream>
#include <Windows.h>
/// <summary>
/// Al instanciar un objeto de esta clase la consola se pone en modo UTF-8. Al finalizar el programa se deja como estaba antes.
/// </summary>
class UTF8CodePage {
public:
    UTF8CodePage() : paginaDeCodigosAntigua(GetConsoleOutputCP()) {
        //En el constructor pongo la página de códigos UTF-8.
        //También guardo la página de códigos actual.
        SetConsoleOutputCP(CP_UTF8);
    }
    ~UTF8CodePage() {
        //En el destructor dejo la página de códigos que estaba.
        SetConsoleOutputCP(paginaDeCodigosAntigua);
    }

private:
    unsigned int paginaDeCodigosAntigua;
};
