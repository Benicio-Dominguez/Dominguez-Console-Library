#include <Windows.h>
#include "Entrada.h"


bool Entrada::EstaAbajo(tecla entrada) {
	if ((GetAsyncKeyState((int)entrada) & 0b1000000000000000) == 0b1000000000000000)
		return true;
	else
		return false;
}

estadoTecla Entrada::EstadoTecla(tecla entrada) {
	static tecla ultimaPresionada;
	//Si entrada está presionada, y es diferente de ultima presionada, devuelvo 1
	if (((GetAsyncKeyState((int)entrada) & 0b1000000000000000) == 0b1000000000000000) && entrada != ultimaPresionada)
	{
		ultimaPresionada = entrada;
		return estadoTecla::presionada;
	}
	else if (((GetAsyncKeyState((int)entrada) & 0b1000000000000000) == 0b1000000000000000)) {
		//Si entrada está presionada, pero ya fue presionada antes, devuelvo 2.
		return estadoTecla::abajo;
	}
	//Si entrada no está presionada, y ultima presionada tampoco, vacio ultima presionada y devuelvo 0.
	else if ((GetAsyncKeyState((int)ultimaPresionada) & 0b1000000000000000) != 0b1000000000000000)
	{
		ultimaPresionada = tecla::Vacio;
		return estadoTecla::suelta;
	}

}

direccionales Entrada::AbajoDireccionales() {
	if (EstaAbajo(tecla::FlechaArriba) && EstaAbajo(tecla::FlechaDerecha))
		return direccionales::arribaDerecha;
	else if (EstaAbajo(tecla::FlechaAbajo) && EstaAbajo(tecla::FlechaDerecha))
		return direccionales::abajoDerecha;
	else if (EstaAbajo(tecla::FlechaAbajo) && EstaAbajo(tecla::FlechaIzquierda))
		return direccionales::abajoIzquierda;
	else if (EstaAbajo(tecla::FlechaArriba) && EstaAbajo(tecla::FlechaIzquierda))
		return direccionales::arribaIzquierda;
	else if (EstaAbajo(tecla::FlechaArriba))
		return direccionales::arriba;
	else if (EstaAbajo(tecla::FlechaDerecha))
		return direccionales::derecha;
	else if (EstaAbajo(tecla::FlechaAbajo))
		return direccionales::abajo;
	else if (EstaAbajo(tecla::FlechaIzquierda))
		return direccionales::izquierda;
	else
		return direccionales::nada;
}

direccionales Entrada::PresionoDireccionales() {
	static direccionales ultimaPresionada;
	if (EstaAbajo(tecla::FlechaArriba) && ultimaPresionada != direccionales::arriba)
	{
		if (EstaAbajo(tecla::FlechaDerecha))
		{
			ultimaPresionada = direccionales::arriba;
			return direccionales::arribaDerecha;
		}
		else if (EstaAbajo(tecla::FlechaIzquierda)) {
			ultimaPresionada = direccionales::arriba;
			return direccionales::arribaIzquierda;
		}
		else
		{
			ultimaPresionada = direccionales::arriba;
			return direccionales::arriba;
		}
	}
	else if (EstaAbajo(tecla::FlechaAbajo) && ultimaPresionada != direccionales::abajo)
	{
		if (EstaAbajo(tecla::FlechaDerecha) && ultimaPresionada != direccionales::abajoDerecha)
		{
			ultimaPresionada = direccionales::abajo;
			return direccionales::abajoDerecha;
		}
		else if (EstaAbajo(tecla::FlechaIzquierda) && ultimaPresionada != direccionales::abajoIzquierda)
		{
			ultimaPresionada = direccionales::abajo;
			return direccionales::abajoIzquierda;
		}
		else
		{
			ultimaPresionada = direccionales::abajo;
			return direccionales::abajo;
		}
	}
	else if (EstaAbajo(tecla::FlechaDerecha) && ultimaPresionada == direccionales::vacio)
	{
		ultimaPresionada = direccionales::derecha;
		return direccionales::derecha;
	}
	else if (EstaAbajo(tecla::FlechaIzquierda) && ultimaPresionada == direccionales::vacio)
	{
		ultimaPresionada = direccionales::izquierda;
		return direccionales::izquierda;
	}
	if (!EstaAbajo(tecla::FlechaArriba) && !EstaAbajo(tecla::FlechaAbajo) && !EstaAbajo(tecla::FlechaIzquierda) && !EstaAbajo(tecla::FlechaDerecha))
	{
		ultimaPresionada = direccionales::vacio;
		return direccionales::nada;
	}
	return direccionales::nada;
}

tecla Entrada::PresionoTeclado() {
	static tecla ultimaSalida;

	if (EstadoTecla(tecla::Q) == estadoTecla::presionada )
		ultimaSalida = tecla::Q;
	else if (EstadoTecla(tecla::W) == estadoTecla::presionada )
		ultimaSalida = tecla::W;
	else if (EstadoTecla(tecla::E) == estadoTecla::presionada )
		ultimaSalida = tecla::E;
	else if (EstadoTecla(tecla::R) == estadoTecla::presionada )
		ultimaSalida = tecla::R;
	else if (EstadoTecla(tecla::T) == estadoTecla::presionada )
		ultimaSalida = tecla::T;
	else if (EstadoTecla(tecla::Y) == estadoTecla::presionada )
		ultimaSalida = tecla::Y;
	else if (EstadoTecla(tecla::U) == estadoTecla::presionada )
		ultimaSalida = tecla::U;
	else if (EstadoTecla(tecla::I) == estadoTecla::presionada )
		ultimaSalida = tecla::I;
	else if (EstadoTecla(tecla::O) == estadoTecla::presionada )
		ultimaSalida = tecla::O;
	else if (EstadoTecla(tecla::P) == estadoTecla::presionada )
		ultimaSalida = tecla::P;
	else if (EstadoTecla(tecla::A) == estadoTecla::presionada )
		ultimaSalida = tecla::A;
	else if (EstadoTecla(tecla::S) == estadoTecla::presionada )
		ultimaSalida = tecla::S;
	else if (EstadoTecla(tecla::D) == estadoTecla::presionada )
		ultimaSalida = tecla::D;
	else if (EstadoTecla(tecla::F) == estadoTecla::presionada )
		ultimaSalida = tecla::F;
	else if (EstadoTecla(tecla::G) == estadoTecla::presionada )
		ultimaSalida = tecla::G;
	else if (EstadoTecla(tecla::H) == estadoTecla::presionada )
		ultimaSalida = tecla::H;
	else if (EstadoTecla(tecla::J) == estadoTecla::presionada )
		ultimaSalida = tecla::J;
	else if (EstadoTecla(tecla::K) == estadoTecla::presionada )
		ultimaSalida = tecla::K;
	else if (EstadoTecla(tecla::L) == estadoTecla::presionada )
		ultimaSalida = tecla::L;
	else if (EstadoTecla(tecla::Z) == estadoTecla::presionada )
		ultimaSalida = tecla::Z;
	else if (EstadoTecla(tecla::X) == estadoTecla::presionada )
		ultimaSalida = tecla::X;
	else if (EstadoTecla(tecla::C) == estadoTecla::presionada )
		ultimaSalida = tecla::C;
	else if (EstadoTecla(tecla::V) == estadoTecla::presionada )
		ultimaSalida = tecla::V;
	else if (EstadoTecla(tecla::B) == estadoTecla::presionada )
		ultimaSalida = tecla::B;
	else if (EstadoTecla(tecla::N) == estadoTecla::presionada )
		ultimaSalida = tecla::N;
	else if (EstadoTecla(tecla::Ñ) == estadoTecla::presionada)
		ultimaSalida = tecla::Ñ;
	else if (EstadoTecla(tecla::M) == estadoTecla::presionada )
		ultimaSalida = tecla::M;
	else if (EstadoTecla(tecla::_0) == estadoTecla::presionada )
		ultimaSalida = tecla::_0;
	else if (EstadoTecla(tecla::_1) == estadoTecla::presionada )
		ultimaSalida = tecla::_1;
	else if (EstadoTecla(tecla::_2) == estadoTecla::presionada )
		ultimaSalida = tecla::_2;
	else if (EstadoTecla(tecla::_3) == estadoTecla::presionada )
		ultimaSalida = tecla::_3;
	else if (EstadoTecla(tecla::_4) == estadoTecla::presionada )
		ultimaSalida = tecla::_4;
	else if (EstadoTecla(tecla::_5) == estadoTecla::presionada )
		ultimaSalida = tecla::_5;
	else if (EstadoTecla(tecla::_6) == estadoTecla::presionada )
		ultimaSalida = tecla::_6;
	else if (EstadoTecla(tecla::_7) == estadoTecla::presionada )
		ultimaSalida = tecla::_7;
	else if (EstadoTecla(tecla::_8) == estadoTecla::presionada )
		ultimaSalida = tecla::_8;
	else if (EstadoTecla(tecla::_9) == estadoTecla::presionada )
		ultimaSalida = tecla::_9;
	else if (EstadoTecla(tecla::Espacio) == estadoTecla::presionada )
		ultimaSalida = tecla::Espacio;
	else if (EstadoTecla(tecla::Retroceso) == estadoTecla::presionada )
		ultimaSalida = tecla::Retroceso;
	else if (EstadoTecla(tecla::Coma) == estadoTecla::presionada)
		ultimaSalida = tecla::Coma;
	else if (EstadoTecla(tecla::Punto) == estadoTecla::presionada)
		ultimaSalida = tecla::Punto;
	else if (EstadoTecla(tecla::Guion) == estadoTecla::presionada)
		ultimaSalida = tecla::Guion;
	else if (EstadoTecla(tecla::Suma) == estadoTecla::presionada)
		ultimaSalida = tecla::Suma;
	else if (EstadoTecla(tecla::Acento) == estadoTecla::presionada)
		ultimaSalida = tecla::Acento;
	else 
		ultimaSalida = tecla::Vacio;

	while (EstadoTecla(ultimaSalida) == estadoTecla::abajo);//Me enclavo esperando a que el usuario libere la tecla, para evitar que haya dos teclas apretadas a la vez.

	return ultimaSalida;
}