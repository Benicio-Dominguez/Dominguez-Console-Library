#include "iostream"
#include "stdlib.h"
#include "ctime"
using namespace std;

//Llenar un vector de 10 posiciones con números enteros aleatorios entre 1 y 10, ordenarlo con el método de selección. Luego mostrar por pantalla 
//el vector ordenado, el máximo y el mínimo.
int Menor(int x, int y, int z);

int main() {

	srand(time(NULL));
	int num = 0, a = 0, i = 0, aux = 0, min = 0, n[10], lista, TAM = 10;

	cout << "¿quiere comenzar con el contador de numeros aleatorios? si=1 no= cualquier otro numero" << endl;
	cin >> a;
	if (a == 1) {

		system("cls");
		cout << "\n\nel orden aleatorio es: ";
		for (i; i <= n[10]; i++) {
			num = rand() % (10 - 1);
			n[i] = num;
			cout << n[i] << ", ";
		}
		for (i = 0; i <= n[10]; i++)
			min = Menor(lista, n[10], i);
		aux = lista[i];
		lista[i] = lista[min];
		lista[min] = aux;

	}
	else {
		system("cls");
		cout << "\n\nhasta la proxima :)";
	}



	return 0;
}

int Menor(int x, int y, int z) {

	for (z = 0; z <= y; z++) {

		if (x < y) {
			x = y;
		}
	}
	return x;
}