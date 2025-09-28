/**********************************************************************************
// Missile (Arquivo de Cabe�alho)
//
// Cria��o:     21 Dez 2012
// Atualiza��o: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   M�sseis do jogo Galaga
//
**********************************************************************************/

#ifndef _GRAVITYGUY_BULLET_H_
#define _GRAVITYGUY_BULLET_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"              // tipos espec�ficos da engine
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
// Fun��es Membro Inline
inline void Bullet::Draw()
{
    sprite->Draw(x, y, z);
}
inline float Bullet::getVel() {
    return vel;
}
// ---------------------------------------------------------------------------------

#endif