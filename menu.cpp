#include "Menu.h"
#include <iostream>

Menu::Menu(Juego& juego)
    : _juego(juego), _window(sf::VideoMode(800, 600), "Menu"), _opcionSeleccionada(1)
{
    _font.loadFromFile("arial.ttf");
    _backgroundTexture.loadFromFile("background.png");
    _background.setTexture(_backgroundTexture);

    _titulo.setFont(_font); _titulo.setString("=== TERRA ==="); _titulo.setCharacterSize(40);
    _opcion1.setFont(_font); _opcion1.setString("1. Jugar"); _opcion1.setCharacterSize(30);
    _opcion2.setFont(_font); _opcion2.setString("2. Creditos"); _opcion2.setCharacterSize(30);
    _opcion3.setFont(_font); _opcion3.setString("3. Salir"); _opcion3.setCharacterSize(30);
}

void Menu::dibujarTexto(sf::Text& texto, float y)
{
    texto.setPosition(_window.getSize().x / 2 - texto.getLocalBounds().width / 2, y);
    _window.draw(texto);
}

void Menu::mostrar()
{
    while (_window.isOpen())
    {
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                _window.close();
            }
            else if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Up)
                {
                    _opcionSeleccionada--;
                    if (_opcionSeleccionada < 1) _opcionSeleccionada = 3;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    _opcionSeleccionada++;
                    if (_opcionSeleccionada > 3) _opcionSeleccionada = 1;
                }
                else if (event.key.code == sf::Keyboard::Enter)
                {
                    switch (_opcionSeleccionada)
                    {
                        case 1:
                            _window.close();
                            _juego.iniciar();
                            mostrar(); /// cuando finaliza vuelve a mostrar el menu
                            return;
                        case 2:
                            mostrarCreditos();
                            break;
                        case 3:
                            _window.close();
                            return;
                    }
                }
            }
        }

        _window.clear();
        _window.draw(_background);

        _opcion1.setFillColor(_opcionSeleccionada == 1 ? sf::Color::Yellow : sf::Color::White);
        _opcion2.setFillColor(_opcionSeleccionada == 2 ? sf::Color::Yellow : sf::Color::White);
        _opcion3.setFillColor(_opcionSeleccionada == 3 ? sf::Color::Yellow : sf::Color::White);

        dibujarTexto(_titulo, 100);
        dibujarTexto(_opcion1, 250);
        dibujarTexto(_opcion2, 300);
        dibujarTexto(_opcion3, 350);

        _window.display();
    }
}

void Menu::mostrarCreditos() {
    sf::RenderWindow creditosWindow(sf::VideoMode(600, 500), "Créditos");

    /// fondo
    sf::Texture fondoTextura;
    if (!fondoTextura.loadFromFile("creditsback.png")) {
        std::cout << "No se pudo cargar creditsback.png" << std::endl;
    }
    sf::Sprite fondo;
    fondo.setTexture(fondoTextura);

    /// creditos
    sf::Text texto;
    texto.setFont(_font);
    texto.setCharacterSize(24);
    texto.setFillColor(sf::Color::White);
    texto.setString("=== CREDITOS ===\n\nGRUPO 40\n\nFederico Leandro Arias\nFranco Agustin Coronel\nNicolás Lautaro Cragno\nMateo Viviani");
    sf::FloatRect textoBounds = texto.getLocalBounds();
    texto.setOrigin(textoBounds.left + textoBounds.width / 2.0f, textoBounds.top + textoBounds.height / 2.0f);
    texto.setPosition(creditosWindow.getSize().x / 3.0f, creditosWindow.getSize().y / 2.0f);

    while (creditosWindow.isOpen()) {
        sf::Event event;
        while (creditosWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                creditosWindow.close();
            } else if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter) {
                    creditosWindow.close();
                }
            }
        }

        ///creditosWindow.clear(sf::Color::Black);
        creditosWindow.draw(fondo);
        creditosWindow.draw(texto);
        creditosWindow.display();
    }
}

