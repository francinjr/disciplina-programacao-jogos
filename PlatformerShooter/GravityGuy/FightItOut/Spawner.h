#pragma once
#pragma once


#ifndef _GRAVITYGUY_SPAWNER_H_
#define _GRAVITYGUY_SPAWNER_H_

// ---------------------------------------------------------------------------------

#include "Types.h"                                      // tipos específicos da engine
#include "Object.h"                                     // interface de Object
#include "Sprite.h"                                     // desenho de sprites
#include "Bullet.h"
#include "Timer.h"
#include "Gun.h"
#include "GunBox.h"
#include <vector>
#include <random>
// ---------------------------------------------------------------------------------
struct SpawnSurface {
    int xi; // diz sobre a superfície da plataforma
    int xf;
    int y;
};
const int MAX_SPAWN = 3;
class Spawner
{
private:
    Timer * timerBuffDrop = nullptr;
    Timer* timerGunDrop = nullptr;
    float delayBuff;
    float delayGun;
    std::vector<SpawnSurface> spawnSurfaces;
public:
    Spawner(float delayBuff, float delayGun, const std::vector<SpawnSurface>& spawnSurfaces);                   // construtor    
    ~Spawner();                            // destrutor
    
    void Generate();
};


#endif