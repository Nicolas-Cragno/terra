#ifndef JUEGO_H
#define JUEGO_H
#include <SFML/Graphics.hpp>
#include "Nivel.h"
#include <memory>

class Juego {
private:
    Jugador jugador;
    sf::RenderWindow window;
    int nivelActual;
    Nivel* nivel;

public:
    Juego();
    void iniciar();
};

#endif
