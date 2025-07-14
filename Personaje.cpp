#include "Personaje.h"
#include <iostream>

Personaje::Personaje() : posicionFila(0), posicionColumna(0) {}

int Personaje::getPosicionFila() const {
    return posicionFila;
}

int Personaje::getPosicionColumna() const {
    return posicionColumna;
}

void Personaje::setPosicionFila(int fila) {
    posicionFila = fila;
}

void Personaje::setPosicionColumna(int columna) {
    posicionColumna = columna;
}

void Personaje::mover(char direccion) {
    int nuevaFila = posicionFila;
    int nuevaColumna = posicionColumna;

    switch (direccion) {
        case 'W': case 'w': nuevaFila--; break;
        case 'S': case 's': nuevaFila++; break;
        case 'A': case 'a': nuevaColumna--; break;
        case 'D': case 'd': nuevaColumna++; break;
        default: return;
    }

    setPosicionFila(nuevaFila);
    setPosicionColumna(nuevaColumna);
}