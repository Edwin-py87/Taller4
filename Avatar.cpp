#include "Avatar.h"
#include <iostream>

Avatar::Avatar() : Personaje() {}

std::string Avatar::getTipo() const {
    return "Avatar";
}

void Avatar::mover(char direccion) {
    int nuevaFila = getPosicionFila();
    int nuevaColumna = getPosicionColumna();

    switch (direccion) {
        case 'W': case 'w': nuevaFila--; break;
        case 'S': case 's': nuevaFila++; break;
        case 'A': case 'a': nuevaColumna--; break;
        case 'D': case 'd': nuevaColumna++; break;
        default: 
            std::cout << "Movimiento inválido. Use W/A/S/D\n";
            return;
    }

    setPosicionFila(nuevaFila);
    setPosicionColumna(nuevaColumna);
}