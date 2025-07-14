#ifndef TABLERO_H
#define TABLERO_H

#include <vector>
#include <string>

enum class TipoCelda {
    VACIO = 0,
    CAMINO = 1,
    ABISMO = 2,
    SALIDA = 3,
    JUGADOR = 4
};

class Tablero {
private:
    std::vector<std::vector<int>> grid;
    int filas;
    int columnas;

    // Métodos privados para generación automática
    void generarTableroAleatorio();
    void crearCaminoSeguro(int fila, int columna);
    void crearCaminoHaciaSalida();
    int contarAbismos() const;

public:
    Tablero();
    void cargarDesdeArchivo(const std::string& archivo);
    bool esPosicionValida(int fila, int columna) const;
    TipoCelda getTipoCelda(int fila, int columna) const;
    int getFilas() const;
    int getColumnas() const;
    bool esSalida(int fila, int columna) const;
};

#endif // TABLERO_H