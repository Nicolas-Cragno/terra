#include "Personaje.h"
#include <iostream>

Personaje::Personaje() {
    velocidadMovimiento = 150.f;
    velocidadAnim = 0.15f;
    frameActual = 0;
    vida = 100;

    filaAnim = 7;
    atacando = false;
    mirandoDerecha = true;
}

void Personaje::setTextura(const std::string& archivo) {
    textura.loadFromFile(archivo);
    sprite.setTexture(textura);
    sprite.setOrigin(FRAME_W /2.f, FRAME_H / 2.f);
    sprite.setTextureRect(sf::IntRect(0, 0, FRAME_W, FRAME_H));
    sprite.setScale(mirandoDerecha ? 2.f : -2.f, 2.f);
}

void Personaje::setPosicion(float x, float y) {
    sprite.setPosition(x, y);
}

sf::Vector2f Personaje::getPosicion() const {
    return sprite.getPosition();
}

sf::FloatRect Personaje::getBounds() const {
    return sprite.getGlobalBounds();
}

void Personaje::mover(float dt, float pisoTop) {
    velocidadY += gravedad * dt;
    sprite.move(0, velocidadY * dt);

    if (sprite.getGlobalBounds().left < 0) {
        sprite.setPosition(sprite.getOrigin().x, sprite.getPosition().y);
    }

    if (sprite.getGlobalBounds().left + sprite.getGlobalBounds().width > 800) {
        sprite.setPosition(800 - (sprite.getGlobalBounds().width - sprite.getOrigin().x), sprite.getPosition().y);
    }

    float spriteBottom = sprite.getPosition().y + (FRAME_H * sprite.getScale().y) / 2.f;
    if (spriteBottom >= pisoTop) {
        sprite.setPosition(sprite.getPosition().x, pisoTop - (FRAME_H * sprite.getScale().y) / 2.f);
        enSuelo = true;
        velocidadY = 0;
    }

}

void Personaje::verificarColisionPiso(const sf::RectangleShape& piso) {
    sf::FloatRect bounds = sprite.getGlobalBounds();
    sf::FloatRect pisoBounds = piso.getGlobalBounds();

    if (bounds.intersects(pisoBounds) && velocidadY >= 0) {
        /// poner justo arriba del piso
        sprite.setPosition(sprite.getPosition().x, pisoBounds.top - bounds.height / 2);
        velocidadY = 0;
        enSuelo = true;
    } else {
        enSuelo = false;
    }
}

void Personaje::atacar() {
    atacando = true;
    filaAnim = 15;
    frameActual = 4; /// piña
    relojAnim.restart();
}

void Personaje::recibirDanio(int cantidad) {
    vida -= (cantidad * 0.2);

    if (vida < 0) {
        vida = 0;
    }

    recibiendoDanio = true;
    relojDanio.restart();
}

bool Personaje::conVida() const {
    return vida > 0;
}

void Personaje::actualizarAnimacion() {
    if (relojAnim.getElapsedTime().asSeconds() >= velocidadAnim) {
        frameActual = (frameActual + 1) % COLUMNS;
        relojAnim.restart();
    }

    if (atacando && frameActual == COLUMNS - 1)
        atacando = false;

    sprite.setTextureRect(sf::IntRect(frameActual * FRAME_W, filaAnim * FRAME_H, FRAME_W, FRAME_H));
    sprite.setScale(mirandoDerecha ? 2.f : -2.f, 2.f);
}

void Personaje::dibujar(sf::RenderWindow& window) {

    if(recibiendoDanio){
        sprite.setColor(sf::Color::Red);

        if(relojDanio.getElapsedTime().asSeconds() > duracionDanio){
            recibiendoDanio = false;
            sprite.setColor(sf::Color::White);
        }
    }

    window.draw(sprite);

}

void Personaje::setFilaAnim(int fila) {
    filaAnim = fila;
}
