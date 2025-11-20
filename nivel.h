#ifndef NIVEL_H
#define NIVEL_H
#include <SFML/Graphics.hpp>
#include "Jugador.h"
#include "Jefe.h"

class Nivel {
private:
    /// gameover
    bool gameOver = false;
    sf::Clock relojGameOver;
    /// personajes, etc
    Jugador* jugador;
    Jefe jefe;
    int nivelActual;
    bool completado;

    /// texturas y visual
    sf::Texture fondoTextura;
    sf::Sprite fondo;
    sf::RectangleShape piso;

    /// barras de vidas
    sf::RectangleShape barraVidaJugadorFondo;
    sf::RectangleShape barraVidaJugador;
    sf::RectangleShape barraVidaJefeFondo;
    sf::RectangleShape barraVidaJefe;
    sf::Font fuente;
    sf::Text textoJugador;
    sf::Text textoJefe;
    sf::Text textoVidas;
    sf::Text textoPuntaje;

public:
    Nivel(int numero, Jugador* refJugador);
    void actualizar(float dt);
    const sf::RectangleShape& getPiso() const;
    void dibujar(sf::RenderWindow& window);
    bool estaCompletado() const { return completado; }
    void reiniciar();
    void finalizar();
    void volverAlMenu();
    sf::Text textoGameOver;
    bool estaGameOver() const { return gameOver; }
    float tiempoGameOver() const { return relojGameOver.getElapsedTime().asSeconds(); }
};

#endif
