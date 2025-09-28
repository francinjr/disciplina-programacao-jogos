/**********************************************************************************
// Missile (Arquivo de Cabeçalho)
//
// Criação:     21 Dez 2012
// Atualização: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Mísseis do jogo Galaga
//
**********************************************************************************/

#ifndef _GRAVITYGUY_BULLET_H_
#define _GRAVITYGUY_BULLET_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"              // tipos específicos da engine
#include "Object.h"             // interface de object
#include "Sprite.h"             // interface de sprites
#include "Image.h"              // interface de image

// ---------------------------------------------------------------------------------

class Bullet : public Object
{
private:
    Sprite* sprite;
    float vel;
    float damage;
public:
    Bullet(Image* img, int side, float damage);
    ~Bullet();

    float getDamage();
    float getVel();
    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline
inline void Bullet::Draw()
{
    sprite->Draw(x, y, z);
}
inline float Bullet::getVel() {
    return vel;
}
// ---------------------------------------------------------------------------------

#endif