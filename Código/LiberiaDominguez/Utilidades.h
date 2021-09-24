#pragma once

/// <summary>
/// Calcula la cantidad de d�gitos en un entero.
/// </summary>
unsigned int cantdigitos(int entero) {
	int cantDigitos = 1;
	while (entero /= 10)
		cantDigitos++;
	return cantDigitos;
}
