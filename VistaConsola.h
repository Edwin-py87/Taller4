#ifndef VISTACONSOLA_H
#define VISTACONSOLA_H

#include "Tablero.h"
#include "IPersonaje.h"
#include <vector>
#include <string>

class VistaConsola {
private:
    Tablero* tablero;
    std::vector<IPersonaje*>& jugadores;

public:
    VistaConsola(Tablero* tab, std::vector<IPersonaje*>& jugs);
    void mostrarJuego();
    void mostrarMensaje(const std::string& mensaje);
    char getEntradaConsola();
};

#endif // VISTACONSOLA_H