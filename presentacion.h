#ifndef PRESENTACION_H
#define PRESENTACION_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

class Presentacion {
private:
    std::vector<sf::Texture> texturas;
    sf::Sprite sprite;
    int indiceActual = 0;
    bool activa = true;

public:
    Presentacion() {}

    /// carga varias imágenes en orden
    void cargar(const std::vector<std::string>& rutas) {
        texturas.clear();
        for (auto& ruta : rutas) {
            sf::Texture tex;
            tex.loadFromFile(ruta);
            texturas.push_back(tex);
        }
        sprite.setTexture(texturas[0]);
    }

    /// Actualiza: si presiona SPACE avanza una imagen
    /// retorna true si ya terminó y hay que cerrar la presentación
    bool actualizar() {
        if (!activa) return true;

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
            indiceActual++;

            // ¿hay otra imagen?
            if (indiceActual < texturas.size()) {
                sprite.setTexture(texturas[indiceActual]);
            } else {
                activa = false;
                return true;
            }

            sf::sleep(sf::milliseconds(150)); // anti spam
        }

        return false; // sigue activa
    }

    void dibujar(sf::RenderWindow& window) {
        if (activa)
            window.draw(sprite);
    }

    bool estaActiva() const { return activa; }
};

#endif
