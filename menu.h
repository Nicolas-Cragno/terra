#ifndef MENU_H
#define MENU_H
#include <SFML/Graphics.hpp>
#include "Juego.h"

class Menu {
public:
    Menu(Juego& juego);
    void mostrar();
    void mostrarCreditos();

private:
    Juego& _juego;
    sf::RenderWindow _window;
    sf::Font _font;
    sf::Texture _backgroundTexture;
    sf::Sprite _background;

    sf::Text _titulo;
    sf::Text _opcion1;
    sf::Text _opcion2;
    sf::Text _opcion3;

    int _opcionSeleccionada;

    void dibujarTexto(sf::Text& texto, float y);
};

#endif
