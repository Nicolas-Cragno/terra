#include "Jefe.h"

Jefe::Jefe() {
    velocidadMovimiento = 100.f;
    filaAnim = 7;
    direccion = 1;
}

void Jefe::configurarLimites(float izq, float der) {
    limiteIzq = izq;
    limiteDer = der;
}

void Jefe::actualizar(float dt, float pisoTop) {
    sprite.move(direccion * velocidadMovimiento * dt, 0);
    float x = sprite.getPosition().x;

    if (x < limiteIzq || x > limiteDer) {
        direccion *= -1;
        mirandoDerecha = !mirandoDerecha;
    }

    /// gravedad
    velocidadY += 980.f * dt;
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


    /// ataque automatico cada x seg
    if (relojAtaque.getElapsedTime().asSeconds() > 1.f) {
        atacar();
        relojAtaque.restart();
    }

    if (!atacando)
        filaAnim = 7; /// piña

    actualizarAnimacion();
}
