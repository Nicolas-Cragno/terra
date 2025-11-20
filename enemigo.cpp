#include <iostream>
using namespace std;
#include "enemigo.h"

Enemigo::Enemigo(const std::string& imgSprite, float x, float y, float limiteIzq, float limiteDer)
{
    _direccion = 1;
    _limiteIzq = limiteIzq;
    _limiteDer = limiteDer;

    _texture.loadFromFile(imgSprite);

    _sprite.setTexture(_texture);
    _sprite.setPosition(x, y);
    _sprite.setScale(3,3); /// más grande (?
}

void Enemigo::update(float deltaTime){
    _sprite.move(_direccion * 100 * delaTime, 0);

    if(_sprite.getPosition().x < limiteIzq){
        _direccion = 1;
    }
    if (_sprite.getPosition().x > limiteDer){
        _direccion = -1;
    }

    Enemigo::update(deltaTime)
}
