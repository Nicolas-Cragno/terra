
#ifndef JEFE_H
#define JEFE_H
#include "Personaje.h"

class Jefe : public Personaje {
private:
    /// fisica
    float limiteIzq;
    float limiteDer;

    /// movimiento
    int direccion;
    sf::Clock relojAtaque;

public:
    Jefe();
    void configurarLimites(float izq, float der);
    void actualizar(float dt, float pisoTop);
};

#endif
