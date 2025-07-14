#ifndef LOGICADEMOVIMIENTO_H
#define LOGICADEMOVIMIENTO_H

#include "IPersonaje.h"
#include "Tablero.h"
#include <vector>

class LogicaDeMovimiento {
private:
    Tablero* tablero;

public:
    LogicaDeMovimiento();
    void setTablero(Tablero* tab);
    void mover(std::vector<IPersonaje*>& personajes, char direccion);
};

#endif // LOGICADEMOVIMIENTO_H