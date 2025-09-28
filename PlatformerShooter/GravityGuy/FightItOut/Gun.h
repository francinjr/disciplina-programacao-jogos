#pragma once

#ifndef _GRAVITYGUY_GUN_H_
#define _GRAVITYGUY_GUN_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
#include "Bullet.h"
#include "Timer.h"
#include "Animation.h"
#include "TileSet.h"
#include "Buff.h"
// ---------------------------------------------------------------------------------

enum GunType{PISTOL, SMG, RIFLE, REVOLVER};
enum GunState {AIM_RIGHT,AIM_LEFT, SHOOT_RIGHT, SHOOT_LEFT};
const float MAX_DAMAGE = 800.0F;

class Gun : public Object
{
private:
    TileSet* gunTileSet = nullptr;
    Animation* anim = nullptr;
    GunState gunState;

    uint ammo = 0; // quant de balas
    float damage = 0.0f; // dano da arma
    GunType gunType;
    float fireRating = 0.0f; // delay para dar o tiro
    Timer* timer = nullptr;
    int playerNumber;
public:
    Gun(int posX, int posY,GunType gunType, int pn);                   // construtor    
    ~Gun();                            // destrutor
    Bullet * Shoot();
    void setState(GunState gunState);
    void setExtraFireRating(float fireRating);
    void setExtraDamage(int extraDamage);
    void changeSide(bool side);
    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline void Gun::setState(GunState gunState) {
    this->gunState = gunState;
}
inline void Gun::setExtraFireRating(float extraFireRating) {
    this->fireRating -= extraFireRating;
    if (fireRating <= 0) fireRating = 0.05f;
}
inline void Gun::setExtraDamage(int extraDamage) {
    this->damage += extraDamage;
    if (damage > MAX_DAMAGE) damage == MAX_DAMAGE;
}
// ---------------------------------------------------------------------------------

#endif