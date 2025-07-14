#ifndef IPERSONAJE_H
#define IPERSONAJE_H

#include <string>

class IPersonaje {
public:
    virtual int getPosicionFila() const = 0;
    virtual int getPosicionColumna() const = 0;
    virtual void mover(char direccion) = 0;
    virtual void setPosicionFila(int fila) = 0;
    virtual void setPosicionColumna(int columna) = 0;
    virtual std::string getTipo() const = 0;
    virtual ~IPersonaje() = default;
};

#endif // IPERSONAJE_H