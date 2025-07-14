#ifndef AVATARCPU_H
#define AVATARCPU_H

#include "Avatar.h"
#include "Tablero.h"
#include <random>

class AvatarCPU : public Avatar {
private:
    std::mt19937 generator;
    std::uniform_int_distribution<int> distribucion;
    Tablero* tablero;
    bool activo;

    bool esMovimientoSeguro(int fila, int columna);
    std::vector<char> obtenerMovimientosValidos();

public:
    AvatarCPU();
    std::string getTipo() const override;
    void mover(char direccion = '\0') override;
    void setTablero(Tablero* tab);
    bool estaActivo() const;
    void desactivar();
};

#endif // AVATARCPU_H