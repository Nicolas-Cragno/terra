#ifndef JUGADOR_H
#define JUGADOR_H
#include "Personaje.h"
#include <cstring>

class Jugador : public Personaje {
private:
    char nombre[10];
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
    void setNombre(const char* n);
    const char* getNombre() const;
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
    void reiniciarVidas();
    void perderVida();
};

#endif
