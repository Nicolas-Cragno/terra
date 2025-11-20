#include "Jugador.h"
#include <SFML/Window/Keyboard.hpp>

Jugador::Jugador() {
    vidas = 3;
    puntaje = 0;
    vida = 100;
}

void Jugador::reiniciarVida() {
    vida = 100;
}

void Jugador::perderVida(){
    if(vidas > 0){
        vidas--;
        reiniciarVida();
    }
}

void Jugador::sumarPuntaje(int cantidad){
    puntaje+=cantidad;
}

void Jugador::manejarInput(float dt, float pisoTop) {
    if(!conVida()) return;

    bool moviendo = false;

    /// moverse p adelante y atras
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        sprite.move(-velocidadMovimiento * dt, 0);
        mirandoDerecha = false;
        filaAnim = 11;
        moviendo = true;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        sprite.move(velocidadMovimiento * dt, 0);
        mirandoDerecha = true;
        filaAnim = 11;
        moviendo = true;
    }

    /// ataque
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !atacando) {
        atacar();
    }

    /// saltar
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && enSuelo) {
        velocidadY = -550.0f;
        enSuelo = false;
    }

    /// grevedad
    velocidadY += gravedad * dt;
    sprite.move(0, velocidadY * dt);

    /// piso
    float spriteBottom = sprite.getPosition().y + (FRAME_H * sprite.getScale().y) / 2.f;
    if (spriteBottom >= pisoTop) {
        sprite.setPosition(sprite.getPosition().x, pisoTop - (FRAME_H * sprite.getScale().y) / 2.f);
        velocidadY = 0;
        enSuelo = true;
    } else {
        enSuelo = false;
    }

    /// animacion cuando esta quieto
    if (!moviendo && !atacando && enSuelo) {
        filaAnim = 10;
    }

    actualizarAnimacion();
}

void Jugador::reiniciarAtaque() {
    atacando = false;
}

