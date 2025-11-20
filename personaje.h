#ifndef PERSONAJE_H
#define PERSONAJE_H
#include <SFML/Graphics.hpp>
#include <string>

class Personaje {
protected:
    sf::Texture textura;
    sf::Sprite sprite;
    float vida;

    /// fisica del juego
    float velocidadAnim;
    float velocidadMovimiento;    float gravedad = 980.0f;
    bool enSuelo = true;
    float velocidadY = 0.0f;

    /// animaciones
    int frameActual;
    int filaAnim;      /// fila del sprite
    bool atacando;
    sf::Clock relojAnim;

    /// estados del sprite
    bool mirandoDerecha;

    /// dibujo del personaje
    static const int FRAME_W = 64;
    static const int FRAME_H = 64;
    static const int COLUMNS = 3; /// tope de columnas del sprite

    /// efectos visuales
    bool recibiendoDanio = false;
    sf::Clock relojDanio;
    const float duracionDanio = 0.3f; /// tiempo "color rojo"

public:
    Personaje();
    virtual ~Personaje() = default;

    /// textura y posicion
    virtual void dibujar(sf::RenderWindow& window);
    virtual void actualizarAnimacion();    void setPosicion(float x, float y);
    void setTextura(const std::string& archivo);
    void setFilaAnim(int fila);

    /// movimientos
    bool estaAtacando() const { return atacando; }
    virtual void mover(float dt, float pisoTop);
    virtual void atacar();
    virtual void recibirDanio(int cantidad);
    void verificarColisionPiso(const sf::RectangleShape& piso);

    /// vidas
    virtual bool conVida() const;
    virtual float getVida() const {return vida;}

    sf::Vector2f getPosicion() const;
    sf::FloatRect getBounds() const;
};

#endif
