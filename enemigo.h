#ifndef ENEMIGO_H
#define ENEMIGO_H


class Enemigo : public Personaje
{
    float _direccion;
    float _limiteIzq, _limiteDer;

    public:
        Enemigo(const std::string& imgSprite, float x, float y, float limiteIzq, float limiteDer);
        void update(float delaTime) override;
};

#endif // ENEMIGO_H
