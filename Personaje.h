#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "IPersonaje.h"

class Personaje : public IPersonaje {
protected:
    int posicionFila;
    int posicionColumna;

public:
    Personaje();
    virtual ~Personaje() = default;

    virtual int getPosicionFila() const override;
    virtual int getPosicionColumna() const override;
    virtual void mover(char direccion) override;
    virtual void setPosicionFila(int fila) override;
    virtual void setPosicionColumna(int columna) override;
};

#endif // PERSONAJE_H