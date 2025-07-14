#include "AvatarCPU.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

AvatarCPU::AvatarCPU() : Avatar(), generator(std::random_device{}()), distribucion(0, 3), tablero(nullptr), activo(true) {}

std::string AvatarCPU::getTipo() const {
    return "AvatarCPU";
}

void AvatarCPU::setTablero(Tablero* tab) {
    tablero = tab;
}

bool AvatarCPU::estaActivo() const {
    return activo;
}

void AvatarCPU::desactivar() {
    activo = false;
}

void AvatarCPU::mover(char direccion) {
    if (!activo) return;

    // Verificar si estamos en un abismo y desactivar si es así
    if (tablero && tablero->getTipoCelda(getPosicionFila(), getPosicionColumna()) == TipoCelda::ABISMO) {
        std::cout << "¡AvatarCPU ha caído en un abismo! Eliminado del juego.\n";
        desactivar();
        return;
    }

    // Obtener movimientos válidos (que no lleven a abismos)
    std::vector<char> movimientosValidos = obtenerMovimientosValidos();

    if (movimientosValidos.empty()) {
        std::cout << "AvatarCPU no puede moverse - no hay movimientos seguros disponibles.\n";
        return;
    }

    // Elegir aleatoriamente de los movimientos válidos
    std::uniform_int_distribution<> dis(0, movimientosValidos.size() - 1);
    char movimiento = movimientosValidos[dis(generator)];

    switch (movimiento) {
        case 'W': 
            std::cout << "AvatarCPU se mueve hacia arriba.\n";
            break;
        case 'S': 
            std::cout << "AvatarCPU se mueve hacia abajo.\n";
            break;
        case 'A': 
            std::cout << "AvatarCPU se mueve hacia la izquierda.\n";
            break;
        case 'D': 
            std::cout << "AvatarCPU se mueve hacia la derecha.\n";
            break;
    }

    Avatar::mover(movimiento);
}

std::vector<char> AvatarCPU::obtenerMovimientosValidos() {
    std::vector<char> movimientosValidos;
    int filaActual = getPosicionFila();
    int columnaActual = getPosicionColumna();

    // Verificar cada posible movimiento
    std::vector<std::pair<char, std::pair<int, int>>> posiblesMovimientos = {
        {'W', {filaActual - 1, columnaActual}},
        {'S', {filaActual + 1, columnaActual}},
        {'A', {filaActual, columnaActual - 1}},
        {'D', {filaActual, columnaActual + 1}}
    };

    for (const auto& mov : posiblesMovimientos) {
        int nuevaFila = mov.second.first;
        int nuevaColumna = mov.second.second;

        if (esMovimientoSeguro(nuevaFila, nuevaColumna)) {
            movimientosValidos.push_back(mov.first);
        }
    }

    return movimientosValidos;
}

bool AvatarCPU::esMovimientoSeguro(int fila, int columna) {
    if (!tablero) return false;

    // Verificar límites del tablero
    if (fila < 0 || fila >= tablero->getFilas() || 
        columna < 0 || columna >= tablero->getColumnas()) {
        return false;
    }

    // Verificar que no sea un abismo
    TipoCelda tipoCelda = tablero->getTipoCelda(fila, columna);
    return tipoCelda != TipoCelda::ABISMO;
}