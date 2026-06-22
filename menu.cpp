#include "Menu.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

Menu::Menu(Juego& juego) : _juego(juego), _window(sf::VideoMode(1500, 800), "Menu"), _opcionSeleccionada(1){
    _font.loadFromFile("arial.ttf");
    _backgroundTexture.loadFromFile("puertoback.png");
    _background.setTexture(_backgroundTexture);

    _titulo.setFont(_font); _titulo.setString("TERRA"); _titulo.setCharacterSize(90);
    _opcion1.setFont(_font); _opcion1.setString("Iniciar partida"); _opcion1.setCharacterSize(40);
    _opcion2.setFont(_font); _opcion2.setString("Ranking histórico"); _opcion2.setCharacterSize(40);
    _opcion3.setFont(_font); _opcion3.setString("Ver créditos"); _opcion3.setCharacterSize(40);
    _opcion4.setFont(_font); _opcion4.setString("Salir"); _opcion4.setCharacterSize(40);
}

void Menu::dibujarTexto(sf::Text& texto, float y) {
    texto.setPosition(_window.getSize().x / 2 - texto.getLocalBounds().width / 2, y);
    _window.draw(texto);
}

void Menu::mostrar(){
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
                    if (_opcionSeleccionada < 1) _opcionSeleccionada = 4;
                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    _opcionSeleccionada++;
                    if (_opcionSeleccionada > 4) _opcionSeleccionada = 1;
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
                            mostrarRanking();
                            break;
                        case 3:
                            mostrarCreditos();
                            break;
                        case 4:
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
        _opcion4.setFillColor(_opcionSeleccionada == 4 ? sf::Color::Yellow : sf::Color::White);


        dibujarTexto(_titulo, 100);
        dibujarTexto(_opcion1, 250);
        dibujarTexto(_opcion2, 300);
        dibujarTexto(_opcion3, 350);
        dibujarTexto(_opcion4, 400);

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
    texto.setString("GRUPO 40\n\nFederico Leandro Arias\nFranco Agustin Coronel\nNicolás Lautaro Cragno\nMateo Viviani");
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

        //creditosWindow.clear(sf::Color::Black);
        creditosWindow.draw(fondo);
        creditosWindow.draw(texto);
        creditosWindow.display();
    }
}

struct JugadorScore {
    std::string nombre;
    int puntaje;
};

void Menu::mostrarRanking() {
    std::ifstream archivo("puntajes.txt");
    std::vector<JugadorScore> scores;

    if (archivo.is_open()) {
        std::string nombre;
        int puntaje;
        while (archivo >> nombre >> puntaje) {
            scores.push_back({nombre, puntaje});
        }
        archivo.close();
    }

    /// ordenar
    std::sort(scores.begin(), scores.end(), [](const JugadorScore& a, const JugadorScore& b){
        return a.puntaje > b.puntaje;
    });

    sf::RenderWindow rankingWindow(sf::VideoMode(600, 500), "Ranking");

    /// fondo igual a créditos
    sf::Texture fondoTextura;
    if (!fondoTextura.loadFromFile("creditsback.png")) {
        std::cout << "No se pudo cargar creditsback.png" << std::endl;
    }
    sf::Sprite fondo;
    fondo.setTexture(fondoTextura);

    /// texto
    sf::Text texto;
    texto.setFont(_font);
    texto.setCharacterSize(24);
    texto.setFillColor(sf::Color::White);

    while (rankingWindow.isOpen()) {
        sf::Event event;
        while (rankingWindow.pollEvent(event)) {
            if (event.type == sf::Event::Closed ||
               (event.type == sf::Event::KeyPressed &&
                (event.key.code == sf::Keyboard::Escape || event.key.code == sf::Keyboard::Enter))) {
                rankingWindow.close();
            }
        }

        std::string contenido = "Ranking\n\n";
        int maxMostrar = std::min(5, (int)scores.size());
        for (int i = 0; i < maxMostrar; ++i) {
            contenido += std::to_string(i+1) + ". " + scores[i].nombre + " - " + std::to_string(scores[i].puntaje) + " puntos\n";
        }
        texto.setString(contenido);

        sf::FloatRect textoBounds = texto.getLocalBounds();
        texto.setOrigin(textoBounds.left + textoBounds.width/2, textoBounds.top + textoBounds.height/2);
        texto.setPosition(rankingWindow.getSize().x/3.f, rankingWindow.getSize().y/2.f);


        rankingWindow.clear();
        rankingWindow.draw(fondo);
        rankingWindow.draw(texto);
        rankingWindow.display();
    }
}
