#include "LogicaDeMovimiento.h"
#include <iostream>

LogicaDeMovimiento::LogicaDeMovimiento() : tablero(nullptr) {}

void LogicaDeMovimiento::setTablero(Tablero* tab) {
    tablero = tab;
}

void LogicaDeMovimiento::mover(std::vector<IPersonaje*>& personajes, char direccion) {
    for (auto personaje : personajes) {
        // Ejecutar movimiento sin verificar - dejar que caigan en abismos
        personaje->mover(direccion);

        // Solo verificar si están fuera de los límites del tablero
        if (tablero && (personaje->getPosicionFila() < 0 || 
                       personaje->getPosicionFila() >= tablero->getFilas() ||
                       personaje->getPosicionColumna() < 0 || 
                       personaje->getPosicionColumna() >= tablero->getColumnas())) {

            // Solo revertir si está fuera de los límites del tablero
            std::cout << personaje->getTipo() << " intentó salir del tablero - movimiento revertido\n";
            // Revertir a una posición segura (centro del tablero)
            personaje->setPosicionFila(6);
            personaje->setPosicionColumna(6);
        }
    }
}