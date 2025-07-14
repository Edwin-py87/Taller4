#include "AvatarInnovador.h"
#include <iostream>
#include <algorithm>
#include <cmath>

AvatarInnovador::AvatarInnovador() : Avatar(), contadorMovimientos(0), generator(std::random_device{}()), tablero(nullptr), activo(true) {}

std::string AvatarInnovador::getTipo() const {
    return "AvatarInnovador";
}

void AvatarInnovador::setTablero(Tablero* tab) {
    tablero = tab;
}

bool AvatarInnovador::estaActivo() const {
    return activo;
}

void AvatarInnovador::desactivar() {
    activo = false;
}

void AvatarInnovador::mover(char direccion) {
    if (!activo) return;

    // Verificar si estamos en un abismo y desactivar si es así
    if (tablero && tablero->getTipoCelda(getPosicionFila(), getPosicionColumna()) == TipoCelda::ABISMO) {
        std::cout << "¡AvatarInnovador ha caído en un abismo! Eliminado del juego.\n";
        desactivar();
        return;
    }

    // Calcular movimiento inteligente que evite abismos
    char movimientoElegido = calcularMovimientoInteligente();

    // Si no se puede mover, quedarse quieto
    if (movimientoElegido == '\0') {
        std::cout << "AvatarInnovador no puede moverse - no hay movimientos seguros disponibles.\n";
        return;
    }

    // Agregar posición actual al historial
    historialPosiciones.push_back({getPosicionFila(), getPosicionColumna()});

    // Mantener solo las últimas 8 posiciones para mejor memoria
    if (historialPosiciones.size() > 8) {
        historialPosiciones.erase(historialPosiciones.begin());
    }

    std::cout << "AvatarInnovador (IA Smart) -> " << movimientoElegido 
              << " [Meta: (10,10), Actual: (" << getPosicionFila() << "," << getPosicionColumna() << ")]"
              << " #" << ++contadorMovimientos << "\n";

    Avatar::mover(movimientoElegido);
}

char AvatarInnovador::calcularMovimientoInteligente() {
    if (!tablero) return 'S'; // Fallback si no hay tablero

    const int META_FILA = 10;
    const int META_COLUMNA = 10;

    int filaActual = getPosicionFila();
    int columnaActual = getPosicionColumna();

    // Obtener todos los movimientos seguros (que no lleven a abismos)
    std::vector<char> movimientosSeguroValidos = obtenerMovimientosValidos();

    if (movimientosSeguroValidos.empty()) {
        return '\0'; // No hay movimientos seguros
    }

    // Calcular distancia a la meta
    int distanciaFila = META_FILA - filaActual;
    int distanciaColumna = META_COLUMNA - columnaActual;

    std::vector<std::pair<char, int>> movimientosConPrioridad;

    // Determinar movimientos que nos acercan a la meta Y son seguros
    for (char mov : movimientosSeguroValidos) {
        int prioridad = 0;

        switch (mov) {
            case 'W':
                if (distanciaFila < 0) prioridad = std::abs(distanciaFila);
                break;
            case 'S':
                if (distanciaFila > 0) prioridad = std::abs(distanciaFila);
                break;
            case 'A':
                if (distanciaColumna < 0) prioridad = std::abs(distanciaColumna);
                break;
            case 'D':
                if (distanciaColumna > 0) prioridad = std::abs(distanciaColumna);
                break;
        }

        movimientosConPrioridad.push_back({mov, prioridad});
    }

    // Ordenar por prioridad (mayor prioridad = nos acerca más a la meta)
    std::sort(movimientosConPrioridad.begin(), movimientosConPrioridad.end(), 
              [](const std::pair<char, int>& a, const std::pair<char, int>& b) {
                  return a.second > b.second;
              });

    // Si hay movimientos que nos acercan a la meta
    if (!movimientosConPrioridad.empty() && movimientosConPrioridad[0].second > 0) {
        return elegirEstrategia(movimientosConPrioridad);
    }

    // Si no hay movimientos que nos acercan, elegir cualquier movimiento seguro
    // que no nos lleve a una posición visitada recientemente
    std::vector<char> movimientosFiltrados;
    for (char mov : movimientosSeguroValidos) {
        int nuevaFila = filaActual;
        int nuevaColumna = columnaActual;

        switch (mov) {
            case 'W': nuevaFila--; break;
            case 'S': nuevaFila++; break;
            case 'A': nuevaColumna--; break;
            case 'D': nuevaColumna++; break;
        }

        if (!posicionVisitadaRecientemente(nuevaFila, nuevaColumna)) {
            movimientosFiltrados.push_back(mov);
        }
    }

    // Si todos los movimientos han sido visitados, usar los seguros
    if (movimientosFiltrados.empty()) {
        movimientosFiltrados = movimientosSeguroValidos;
    }

    // Elegir aleatoriamente de los movimientos filtrados
    if (!movimientosFiltrados.empty()) {
        std::uniform_int_distribution<> dis(0, movimientosFiltrados.size() - 1);
        return movimientosFiltrados[dis(generator)];
    }

    return '\0';
}

std::vector<char> AvatarInnovador::obtenerMovimientosValidos() {
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

bool AvatarInnovador::esMovimientoSeguro(int fila, int columna) {
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

char AvatarInnovador::elegirEstrategia(const std::vector<std::pair<char, int>>& movimientosConPrioridad) {
    if (movimientosConPrioridad.empty()) {
        return '\0';
    }

    // Estrategia 1: Movimiento directo (70% del tiempo)
    if (contadorMovimientos % 10 < 7) {
        return movimientosConPrioridad[0].first;
    }

    // Estrategia 2: Alternar entre las dos direcciones principales (20% del tiempo)
    else if (contadorMovimientos % 10 < 9) {
        if (movimientosConPrioridad.size() >= 2) {
            // Alternar entre la primera y segunda prioridad
            return (contadorMovimientos % 2 == 0) ? movimientosConPrioridad[0].first : movimientosConPrioridad[1].first;
        }
        return movimientosConPrioridad[0].first;
    }

    // Estrategia 3: Movimiento con cierta aleatoriedad (10% del tiempo)
    else {
        // Elegir entre los 2 mejores movimientos disponibles
        int limite = std::min(2, static_cast<int>(movimientosConPrioridad.size()));
        std::uniform_int_distribution<> dis(0, limite - 1);
        return movimientosConPrioridad[dis(generator)].first;
    }
}

char AvatarInnovador::movimientoDiagonalInteligente() {
    // Esta función ya no es necesaria ya que obtenerMovimientosValidos()
    // maneja la seguridad, pero la mantenemos para compatibilidad
    std::vector<char> movimientosValidos = obtenerMovimientosValidos();

    if (movimientosValidos.empty()) {
        return '\0';
    }

    // Elegir aleatoriamente de los movimientos válidos
    std::uniform_int_distribution<> dis(0, movimientosValidos.size() - 1);
    return movimientosValidos[dis(generator)];
}

bool AvatarInnovador::posicionVisitadaRecientemente(int fila, int columna) {
    // Solo considerar las últimas 4 posiciones para no ser muy restrictivo
    int limite = std::min(4, static_cast<int>(historialPosiciones.size()));

    for (int i = historialPosiciones.size() - limite; i < historialPosiciones.size(); i++) {
        if (historialPosiciones[i].first == fila && historialPosiciones[i].second == columna) {
            return true;
        }
    }
    return false;
}