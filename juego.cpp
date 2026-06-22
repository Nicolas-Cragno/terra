#include "Juego.h"
#include "Menu.h"
#include <iostream>
#include <fstream>


Juego::Juego() : window(sf::VideoMode(1500, 800), "TERRA") {
    nivelActual = 1;
    jugador.setTextura("iosar.png");
    jugador.setPosicion(50, 600); /// abajo izq
    nivel = new Nivel(nivelActual, &jugador);
}

void Juego::guardarPuntaje() {
    std::ofstream archivo("puntajes.txt", std::ios::app);
    if (archivo.is_open()) {
        archivo << jugador.getNombre() << " " << jugador.getPuntaje() << "\n";
        archivo.close();
    }
}

void Juego::reiniciarJuego() {
    nivelActual = 1;
    jugador.reiniciarVida();
    jugador.reiniciarVidas();
    jugador.setPosicion(50, 600);
}

void Juego::iniciar() {
   bool esMenu = false;
    sf::Clock reloj;

    /// nombre del jugador
    sf::Font font;
    font.loadFromFile("Arial.ttf");


    sf::Text textoNombre;
    textoNombre.setFont(font);
    textoNombre.setCharacterSize(45);
    textoNombre.setFillColor(sf::Color::White);
    textoNombre.setPosition(500.f, 300.f);

    std::string nombreJugador;
    bool nombreIngresado = false;

    while (window.isOpen() && !nombreIngresado) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            else if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode == '\b') {
                    if (!nombreJugador.empty()) nombreJugador.pop_back();
                } else if (event.text.unicode == '\r') {
                    if (!nombreJugador.empty()) nombreIngresado = true;
                } else if (nombreJugador.size() < 10) {
                    nombreJugador += static_cast<char>(event.text.unicode);
                }
            }
        }

        textoNombre.setString("Ingrese su nombre: " + nombreJugador);

        window.clear(sf::Color::Black);
        window.draw(textoNombre);
        window.display();
    }

    if (!nombreJugador.empty())
        jugador.setNombre(nombreJugador.c_str());
    else
        jugador.setNombre("Jugador NN"); /// valor por defecto

    nivel = new Nivel(nivelActual, &jugador);

    /// juego en si
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
                //window.close();
                sf::Font fuente;
                fuente.loadFromFile("Arial.ttf");
                sf::Text cartel;
                cartel.setFont(fuente);
                cartel.setCharacterSize(100);
                cartel.setFillColor(sf::Color::Green);
                cartel.setString("GANASTE!");
                cartel.setPosition(1500 / 2.f - cartel.getLocalBounds().width / 2, 800 / 2.f - cartel.getLocalBounds().height / 2);
                window.clear();
                window.draw(cartel);
                window.display();
                guardarPuntaje();
                delete nivel;
                nivel = nullptr;
                esMenu = true;
                break;
            }
            delete nivel;
            nivel = new Nivel(nivelActual, &jugador);
        }

        if (nivel->estaGameOver() && nivel->tiempoGameOver() > 3.f) {
                guardarPuntaje();
                delete nivel;
                nivel = nullptr;
                esMenu = true;
                break; /// sale del while del juegoo
        } else {
        window.clear();
        nivel->dibujar(window);
        window.display();
        }
    }


        if (window.isOpen()) {
            reiniciarJuego();
            nivel = new Nivel(nivelActual, &jugador);
            Menu menu(*this);
            menu.mostrar();
        }

}


