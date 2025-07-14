#include "Tablero.h"
#include <iostream>
#include <fstream>
#include <random>
#include <ctime>

Tablero::Tablero() : filas(12), columnas(12) {
    generarTableroAleatorio();
}

void Tablero::generarTableroAleatorio() {
    // Inicializar generador de números aleatorios
    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> dis(1, 100);

    // Inicializar todo como camino
    grid.resize(filas, std::vector<int>(columnas, 1));

    // Crear bordes de abismo
    for (int i = 0; i < filas; i++) {
        grid[i][0] = 2; // Abismo izquierdo
        grid[i][columnas-1] = 2; // Abismo derecho
    }
    for (int j = 0; j < columnas; j++) {
        grid[0][j] = 2; // Abismo superior
        grid[filas-1][j] = 2; // Abismo inferior
    }

    // Generar abismos internos aleatorios (15% de probabilidad)
    for (int i = 2; i < filas-2; i++) {
        for (int j = 2; j < columnas-2; j++) {
            if (dis(gen) <= 15) { // 15% de probabilidad
                grid[i][j] = 2; // Abismo
            }
        }
    }

    // Crear algunos clusters de abismos para hacer el tablero más interesante
    int numClusters = 3 + (dis(gen) % 3); // Entre 3 y 5 clusters

    for (int cluster = 0; cluster < numClusters; cluster++) {
        int centroFila = 2 + (dis(gen) % (filas - 4));
        int centroColumna = 2 + (dis(gen) % (columnas - 4));

        // Crear un cluster de 2x2 o 3x3
        int tamano = 2 + (dis(gen) % 2); // 2 o 3

        for (int i = centroFila; i < centroFila + tamano && i < filas-1; i++) {
            for (int j = centroColumna; j < centroColumna + tamano && j < columnas-1; j++) {
                if (dis(gen) <= 70) { // 70% de probabilidad dentro del cluster
                    grid[i][j] = 2;
                }
            }
        }
    }

    // Asegurar que las posiciones iniciales estén libres
    grid[1][1] = 1; // Avatar humano
    grid[1][2] = 1; // AvatarCPU
    grid[2][1] = 1; // AvatarInnovador

    // Crear algunos caminos seguros desde las posiciones iniciales
    crearCaminoSeguro(1, 1);
    crearCaminoSeguro(1, 2);
    crearCaminoSeguro(2, 1);

    // Salida en esquina inferior derecha
    grid[filas-2][columnas-2] = 3;

    // Asegurar que hay un camino hacia la salida
    crearCaminoHaciaSalida();

    std::cout << "Tablero generado automáticamente con " << contarAbismos() << " abismos.\n";
}

void Tablero::crearCaminoSeguro(int fila, int columna) {
    // Crear un pequeño camino seguro desde la posición inicial
    for (int i = 0; i < 3; i++) {
        if (fila + i < filas-1) grid[fila + i][columna] = 1;
        if (columna + i < columnas-1) grid[fila][columna + i] = 1;
    }
}

void Tablero::crearCaminoHaciaSalida() {
    // Crear un camino básico hacia la salida
    int salidaFila = filas - 2;
    int salidaColumna = columnas - 2;

    // Limpiar algunas casillas alrededor de la salida
    for (int i = salidaFila - 2; i <= salidaFila; i++) {
        for (int j = salidaColumna - 2; j <= salidaColumna; j++) {
            if (i > 0 && i < filas-1 && j > 0 && j < columnas-1) {
                if (grid[i][j] == 2) {
                    // 50% de probabilidad de limpiar abismos cerca de la salida
                    std::mt19937 gen(static_cast<unsigned int>(std::time(nullptr)));
                    std::uniform_int_distribution<> dis(1, 100);
                    if (dis(gen) <= 50) {
                        grid[i][j] = 1;
                    }
                }
            }
        }
    }
}

int Tablero::contarAbismos() const {
    int contador = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (grid[i][j] == 2) contador++;
        }
    }
    return contador;
}

void Tablero::cargarDesdeArchivo(const std::string& archivo) {
    std::ifstream file(archivo);
    if (!file.is_open()) {
        std::cout << "No se pudo abrir el archivo " << archivo << ". Usando tablero generado automáticamente.\n";
        generarTableroAleatorio();
        return;
    }

    file >> filas >> columnas;
    grid.resize(filas, std::vector<int>(columnas));

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            file >> grid[i][j];
        }
    }
    file.close();
    std::cout << "Tablero cargado desde archivo: " << archivo << "\n";
}

bool Tablero::esPosicionValida(int fila, int columna) const {
    return fila >= 0 && fila < filas && columna >= 0 && columna < columnas && grid[fila][columna] != 2;
}

TipoCelda Tablero::getTipoCelda(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return TipoCelda::ABISMO;
    }
    return static_cast<TipoCelda>(grid[fila][columna]);
}

int Tablero::getFilas() const { 
    return filas; 
}

int Tablero::getColumnas() const { 
    return columnas; 
}

bool Tablero::esSalida(int fila, int columna) const {
    return getTipoCelda(fila, columna) == TipoCelda::SALIDA;
}