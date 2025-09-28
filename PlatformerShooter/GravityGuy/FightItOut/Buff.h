#pragma once


#ifndef _GRAVITYGUY_BUFF_H_
#define _GRAVITYGUY_BUFF_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
#include "Timer.h"
#include "Animation.h"
#include "TileSet.h"
// ---------------------------------------------------------------------------------
enum BuffType {SHIELD, HEAL, RAPID_FIRE, EXTRA_DAMAGE};

class Buff : public Object
{
private:
    TileSet* tileset = nullptr;
    Animation* anim = nullptr;
    float finalY;
    float finalX;
    Timer* timer = nullptr;
    int duration = 0;
    BuffType buffType;
public:
    Buff(BuffType buff, float finalX, float finalY);                   // construtor    
    ~Buff();                            // destrutor
    float Bottom();
    BuffType GetBuffType();
    void Update();                          // atualização do objeto
    void Draw();                            // desenho do objeto
};

// ---------------------------------------------------------------------------------

inline float Buff::Bottom()
{
    return y + (tileset->TileHeight() / 2.0);
}
inline BuffType Buff::GetBuffType()
{
    return buffType;
}
// ---------------------------------------------------------------------------------

#endif