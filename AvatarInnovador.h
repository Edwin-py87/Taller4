#ifndef AVATARINNOVADOR_H
#define AVATARINNOVADOR_H

#include "Avatar.h"
#include "Tablero.h"
#include <vector>
#include <random>

class AvatarInnovador : public Avatar {
private:
    std::vector<std::pair<int, int>> historialPosiciones;
    int contadorMovimientos;
    std::mt19937 generator;
    Tablero* tablero;
    bool activo;

    char calcularMovimientoInteligente();
    char elegirEstrategia(const std::vector<std::pair<char, int>>& movimientosConPrioridad);
    char movimientoDiagonalInteligente();
    bool posicionVisitadaRecientemente(int fila, int columna);
    bool esMovimientoSeguro(int fila, int columna);
    std::vector<char> obtenerMovimientosValidos();

public:
    AvatarInnovador();
    std::string getTipo() const override;
    void mover(char direccion = '\0') override;
    void setTablero(Tablero* tab);
    bool estaActivo() const;
    void desactivar();
};

#endif // AVATARINNOVADOR_H