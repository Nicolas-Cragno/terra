
#include "Nivel.h"
#include <iostream>

Nivel::Nivel(int numero, Jugador* refJugador) {
    jugador = refJugador;
    nivelActual = numero;
    completado = false;

    /// barras de vida
    float barraMargen = 30.f;
    float barraAncho = 200.f;
    float barraAlto = 20.f;

     /// barra del jugador
    barraVidaJugadorFondo.setSize(sf::Vector2f(barraAncho, barraAlto));
    barraVidaJugadorFondo.setFillColor(sf::Color(50, 50, 50));
    barraVidaJugadorFondo.setPosition(barraMargen, barraMargen);

    barraVidaJugador.setSize(sf::Vector2f(barraAncho, barraAlto));
    barraVidaJugador.setFillColor(sf::Color::Green);
    barraVidaJugador.setPosition(barraMargen, barraMargen);

    /// barras del malo
    barraVidaJefeFondo.setSize(sf::Vector2f(barraAncho, barraAlto));
    barraVidaJefeFondo.setFillColor(sf::Color(50, 50, 50));
    barraVidaJefeFondo.setPosition(1500.f - barraAncho - barraMargen, barraMargen);

    barraVidaJefe.setSize(sf::Vector2f(barraAncho, barraAlto));
    barraVidaJefe.setFillColor(sf::Color::Red);
    barraVidaJefe.setPosition(1500.f - barraAncho - barraMargen, barraMargen);

    /// textos para las barrass
    fuente.loadFromFile("arial.ttf");

    textoJugador.setFont(fuente);
    textoJugador.setCharacterSize(18);
    textoJugador.setFillColor(sf::Color::White);
    textoJugador.setString("Iosar");
    textoJugador.setPosition(
    barraMargen + barraAncho / 2 - textoJugador.getLocalBounds().width / 2, barraMargen - 25.f);

    /// VIDAS
    textoVidas.setFont(fuente);
    textoVidas.setCharacterSize(16);
    textoVidas.setFillColor(sf::Color::Cyan);
    textoVidas.setString("Vidas: " + jugador->getVidas());
    textoVidas.setPosition(barraMargen,barraMargen + barraAlto + 5.f);

    /// puntaje
    textoPuntaje.setFont(fuente);
    textoPuntaje.setCharacterSize(16);
    textoPuntaje.setFillColor(sf::Color::White);
    textoPuntaje.setString("Puntaje: " + jugador->getPuntaje());
    textoPuntaje.setPosition(barraMargen,barraMargen + barraAlto + 25.f);

    /// texto jefe
    textoJefe.setFont(fuente);
    textoJefe.setCharacterSize(18);
    textoJefe.setFillColor(sf::Color::White);
    textoJefe.setString("Magnus");
    textoJefe.setPosition(
    1500.f - barraAncho - barraMargen + barraAncho / 2 - textoJefe.getLocalBounds().width / 2, barraMargen - 25.f);

    /// fondo de pantalla
    std::string fondoPath, jefePath;
    if (numero == 1) {
            fondoPath = "background-one.png"; jefePath = "boss-one.png";
    }else if (numero == 2) {
        fondoPath = "background-two.png"; jefePath = "boss-two.png";
        }else {
            fondoPath = "background-three.png"; jefePath = "boss-three.png";
        }

    fondoTextura.loadFromFile(fondoPath);
    fondo.setTexture(fondoTextura);
    fondo.setScale(1.f, 1.f);

    /// piso del juego
    piso.setSize(sf::Vector2f(1500.f, 150.f));
    piso.setPosition(0.f, 660.f);

    switch(numero){
        case 1: piso.setFillColor(sf::Color(230, 230, 255)); /// nieve
        break;
        case 2: piso.setFillColor(sf::Color(100,100,100)); /// asfalto
        break;
        case 3: piso.setFillColor(sf::Color(50, 200, 50)); /// pasto
        break;
        default: piso.setFillColor(sf::Color(150,150,150));  /// gris
        break;
     }

    /// jefe
    jefe.setTextura(jefePath);
    jefe.setPosicion(700, 400);
    jefe.configurarLimites(500, 800);

    /// game over
    fuente.loadFromFile("arial.ttf");
    textoGameOver.setFont(fuente);
    textoGameOver.setCharacterSize(100);
    textoGameOver.setFillColor(sf::Color::Red);
    textoGameOver.setString("GAME OVER");
    textoGameOver.setPosition(
        1500.f / 2 - textoGameOver.getLocalBounds().width / 2,
        800.f / 2 - textoGameOver.getLocalBounds().height / 2
    );

}

void Nivel::actualizar(float dt) {
     if (gameOver) {
        if (relojGameOver.getElapsedTime().asSeconds() > 3.f) {
            volverAlMenu();
        }
        return;
    }

    /// actualizar personajes
    jugador->manejarInput(dt, piso.getPosition().y);
    jugador->verificarColisionPiso(piso);
    jefe.actualizar(dt, piso.getPosition().y);
    jefe.verificarColisionPiso(piso);

    /// combatee

    if (jugador->estaAtacando() && jugador->getBounds().intersects(jefe.getBounds())){
        jefe.recibirDanio(1); /// pierde vida el jefe
        jugador->sumarPuntaje(10);
    }

    if (jefe.estaAtacando() && jefe.getBounds().intersects(jugador->getBounds())){
        jugador->recibirDanio(1); /// pierde vida el jugador
        if (jugador->getVida() <= 0) {
        jugador->perderVida();
        if (jugador->getVidas() > 0) {
            reiniciar();
        }
        if (jugador->getVidas() <= 0){
            gameOver = true;
            relojGameOver.restart();
        }
    }
        jugador->sumarPuntaje(-5);
    }

    if (!jefe.conVida()) completado = true;


    /*
    if (!jugador->conVida()){
        jugador->perderVida();

        if(jugador->getVida() > 0){
            reiniciar(); /// reiniciar nivel
        }
    }
    */

    /// actualizacion de barras
    float vidaJugador = jugador->getVida();
    float vidaJefe = jefe.getVida();

    barraVidaJugador.setSize(sf::Vector2f(vidaJugador * 2, 20));
    barraVidaJefe.setSize(sf::Vector2f(vidaJefe * 2, 20));
        textoVidas.setString("Vidas: " + std::to_string(jugador->getVidas()));


    if (vidaJugador < 30)
        {barraVidaJugador.setFillColor(sf::Color::Red);}
    else if (vidaJugador < 60)
        {barraVidaJugador.setFillColor(sf::Color::Yellow);}
    else
        {barraVidaJugador.setFillColor(sf::Color::Green);}

    if (vidaJefe < 30)
        {barraVidaJefe.setFillColor(sf::Color(255, 100, 100));}
    else if (vidaJefe < 60)
        {barraVidaJefe.setFillColor(sf::Color(255, 180, 100));}
    else
        {barraVidaJefe.setFillColor(sf::Color::Red);}

}

void Nivel::dibujar(sf::RenderWindow& window) {
    /// escenarios
    window.draw(fondo);
    window.draw(piso);
    /// personajes
    jugador->dibujar(window);
    jefe.dibujar(window);


    /// barras de vida y texto
    window.draw(barraVidaJugadorFondo);
    window.draw(barraVidaJugador);
    window.draw(textoJugador);
    window.draw(textoVidas);

    window.draw(barraVidaJefeFondo);
    window.draw(barraVidaJefe);
    window.draw(textoJefe);

    /// game over
     if (gameOver) {
        sf::Text cartel;
        cartel.setFont(fuente);
        cartel.setCharacterSize(100);
        cartel.setFillColor(sf::Color::Red);
        cartel.setString("GAME OVER");
        cartel.setPosition(1500 / 2.f - cartel.getLocalBounds().width / 2, 800 / 2.f - cartel.getLocalBounds().height / 2);
        window.draw(cartel);
    }
}

void Nivel::reiniciar() {
    completado = false;

    jugador->setPosicion(0, 600);
}

void Nivel::volverAlMenu() {
    /// reiniciar p/desp
    gameOver = false;
    completado = false;
    jugador->setPosicion(0, 600);
    jugador->reiniciarVida();
    jefe.setPosicion(700, 400);
    jefe.recibirDanio(-1000);
}
