#include "Juego.h"
#include <iostream>

Juego::Juego(Tablero* tab, std::vector<IPersonaje*>& jugs, LogicaDeMovimiento* logica, bool estado) 
    : tablero(tab), jugadores(jugs), logicaMovimiento(logica), activo(estado) {
    logicaMovimiento->setTablero(tablero);
}

bool Juego::getEstado() const {
    return activo;
}

void Juego::mover() {
    // Verificar si el Avatar humano cayó en un abismo (solo el Avatar humano termina el juego)
    for (const auto& jugador : jugadores) {
        if (jugador->getTipo() == "Avatar") {
            if (tablero->getTipoCelda(jugador->getPosicionFila(), jugador->getPosicionColumna()) == TipoCelda::ABISMO) {
                std::cout << "\n¡El Avatar humano ha caído en un abismo! ¡Juego terminado!\n";
                std::cout << "Posición del abismo: (" << jugador->getPosicionFila() << ", " << jugador->getPosicionColumna() << ")\n";
                activo = false;
                return;
            }
        }
    }

    // Verificar si algún jugador llegó a la salida
    for (const auto& jugador : jugadores) {
        if (tablero->esSalida(jugador->getPosicionFila(), jugador->getPosicionColumna())) {
            std::cout << "\n¡" << jugador->getTipo() << " ha llegado a la salida! ¡Juego terminado!\n";
            std::cout << "¡" << jugador->getTipo() << " es el ganador!\n";
            activo = false;
            return;
        }
    }
}

void Juego::terminar() {
    activo = false;
}