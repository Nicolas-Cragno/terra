#ifndef JUGADOR_H
#define JUGADOR_H
#include "Personaje.h"

class Jugador : public Personaje {
private:
    /// fisica
    float velocidadY = 0.0f;
    bool enSuelo = true;
    const float gravedad = 980.0f;
    const float impulsoSalto = -450.0f;

    /// contadores
    int vidas;
    int puntaje;

public:
    Jugador();

    /// movimiento y ataque
    void manejarInput(float dt, float pisoTop);
    void reiniciarAtaque();

    /// contadores
    int getPuntaje() const { return puntaje; }
    int getVidas() const { return vidas; }
    void agregarPuntaje(int valor) { puntaje += valor; }
    void sumarPuntaje(int cantidad);

    /// vidas
    void reiniciarVida();
    void perderVida();
};

#endif
