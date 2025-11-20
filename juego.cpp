#include "Juego.h"
#include "Menu.h"
#include <iostream>



Juego::Juego() : window(sf::VideoMode(1500, 800), "TERRA") {
    nivelActual = 1;
    jugador.setTextura("iosar.png");
    jugador.setPosicion(50, 600); /// abajo izq
    nivel = new Nivel(nivelActual, &jugador);
}

void Juego::iniciar() {
   bool esMenu = false;
    sf::Clock reloj;
    while (window.isOpen() && !esMenu) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = reloj.restart().asSeconds();
        nivel->actualizar(dt);

        if (nivel->estaCompletado()) {
            nivelActual++;
            if (nivelActual > 3) {
                window.close();
                break;
            }
            delete nivel;
            nivel = new Nivel(nivelActual, &jugador);
        }

        if (nivel->estaGameOver() && nivel->tiempoGameOver() > 3.f) {
                window.close();
                break;
        } else {
        window.clear();
        nivel->dibujar(window);
        window.display();
        }
    }


    Menu menu(*this);

}
