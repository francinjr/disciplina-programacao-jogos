/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
//
// Criação:     23 Nov 2011
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para um míssil
//
**********************************************************************************/

#ifndef _GEOWARS_MISSILE_H_
#define _GEOWARS_MISSILE_H_

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 

class Missile : public Object
{
private:
    const float MaxDistance = 4406;
    const float BaseVolume = 0.8f;

    static Player*& player;
    Sprite* sprite;
    Vector speed;
    int damage = 10; // Adicionado: Dano que o míssil causa

public:
    Missile();
    ~Missile();

    void OnCollision(Object* obj) override;
    Vector& Speed();
    void Update();
    void Draw();
};

inline Vector& Missile::Speed()
{
    return speed;
}

inline void Missile::Draw()
{
    sprite->Draw(x, y, Layer::UPPER, scale, rotation);
}

#endif