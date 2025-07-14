#ifndef JUEGO_H
#define JUEGO_H

#include "Tablero.h"
#include "IPersonaje.h"
#include "LogicaDeMovimiento.h"
#include <vector>

class Juego {
private:
    Tablero* tablero;
    std::vector<IPersonaje*>& jugadores;
    LogicaDeMovimiento* logicaMovimiento;
    bool activo;

public:
    Juego(Tablero* tab, std::vector<IPersonaje*>& jugs, LogicaDeMovimiento* logica, bool estado = true);
    bool getEstado() const;
    void mover();
    void terminar();
};

#endif // JUEGO_H