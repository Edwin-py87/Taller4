#include "VistaConsola.h"
#include "AvatarCPU.h"
#include "AvatarInnovador.h"
#include <iostream>
#include <cstdlib>

VistaConsola::VistaConsola(Tablero* tab, std::vector<IPersonaje*>& jugs) : tablero(tab), jugadores(jugs) {}

void VistaConsola::mostrarJuego() {
    #ifdef _WIN32
        system("cls");
    #else
        int result = system("clear");
        (void)result; // Evitar warning de unused result
    #endif

    std::cout << "=== JUEGO AVATAR CON POLIMORFISMO ===\n\n";
    std::cout << "Leyenda: . = Camino, # = Abismo, X = Salida\n";
    std::cout << "         A = Avatar, C = CPU, I = Innovador\n\n";

    for (int i = 0; i < tablero->getFilas(); i++) {
        for (int j = 0; j < tablero->getColumnas(); j++) {
            char simbolo = ' ';

            // Verificar si hay un jugador activo en esta posición
            bool hayJugador = false;
            for (const auto& jugador : jugadores) {
                if (jugador->getPosicionFila() == i && jugador->getPosicionColumna() == j) {
                    // Verificar si el jugador está activo
                    bool jugadorActivo = true;

                    if (jugador->getTipo() == "AvatarCPU") {
                        AvatarCPU* cpu = static_cast<AvatarCPU*>(jugador);
                        jugadorActivo = cpu->estaActivo();
                    } else if (jugador->getTipo() == "AvatarInnovador") {
                        AvatarInnovador* innovador = static_cast<AvatarInnovador*>(jugador);
                        jugadorActivo = innovador->estaActivo();
                    }

                    if (jugadorActivo) {
                        if (jugador->getTipo() == "Avatar") simbolo = 'A';
                        else if (jugador->getTipo() == "AvatarCPU") simbolo = 'C';
                        else if (jugador->getTipo() == "AvatarInnovador") simbolo = 'I';
                        hayJugador = true;
                        break;
                    }
                }
            }

            if (!hayJugador) {
                switch (tablero->getTipoCelda(i, j)) {
                    case TipoCelda::CAMINO: simbolo = '.'; break;
                    case TipoCelda::ABISMO: simbolo = '#'; break;
                    case TipoCelda::SALIDA: simbolo = 'X'; break;
                    default: simbolo = ' '; break;
                }
            }

            std::cout << simbolo << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nPosiciones:\n";
    for (const auto& jugador : jugadores) {
        // Mostrar estado del jugador
        std::string estado = " (ACTIVO)";

        if (jugador->getTipo() == "AvatarCPU") {
            AvatarCPU* cpu = static_cast<AvatarCPU*>(jugador);
            if (!cpu->estaActivo()) estado = " (ELIMINADO)";
        } else if (jugador->getTipo() == "AvatarInnovador") {
            AvatarInnovador* innovador = static_cast<AvatarInnovador*>(jugador);
            if (!innovador->estaActivo()) estado = " (ELIMINADO)";
        }

        std::cout << jugador->getTipo() << ": (" 
                  << jugador->getPosicionFila() << ", " 
                  << jugador->getPosicionColumna() << ")" << estado << "\n";
    }
}

void VistaConsola::mostrarMensaje(const std::string& mensaje) {
    std::cout << "\n" << mensaje << " ";
}

char VistaConsola::getEntradaConsola() {
    char entrada;
    std::cin >> entrada;
    return entrada;
}