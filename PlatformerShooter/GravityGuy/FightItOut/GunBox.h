#pragma once


#ifndef _GRAVITYGUY_GUNBOX_H_
#define _GRAVITYGUY_GUNBOX_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
#include "Bullet.h"
#include "Timer.h"
#include "Gun.h"
// ---------------------------------------------------------------------------------

class GunBox : public Object
{
private:
    Sprite* sprite = nullptr;            // sprite da plataforma
    GunType gun;
    float finalY;
    float finalX;
public:
    GunBox(GunType gun, float finalX, float finalY);                   // construtor    
    ~GunBox();                            // destrutor
    void OnCollision(Object* obj);
    GunType GetGunType();
    float Bottom();
    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline float GunBox::Bottom()
{
    return y + (sprite->Height() / 2.0);
}
inline GunType GunBox::GetGunType() {
    return gun;
}
// ---------------------------------------------------------------------------------

#endif