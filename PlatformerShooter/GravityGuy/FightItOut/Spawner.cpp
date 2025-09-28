
#include "Spawner.h"
#include "GravityGuy.h"
#include "Platform.h"
#include "GunBox.h"
#include "Buff.h"
#include "SpawnRegistry.h"
// ---------------------------------------------------------------------------------

std::random_device rd;
std::mt19937 mt(rd());


Spawner::Spawner(float delayBuff, float delayGun, const std::vector<SpawnSurface> & spawnSurfaces)
{
    this->delayGun = delayGun;
    this->delayBuff = delayBuff;
    
    timerGunDrop = new Timer();
    timerGunDrop->Start();

    timerBuffDrop = new Timer();
    timerBuffDrop->Start();

    this->spawnSurfaces = spawnSurfaces;
}

// ---------------------------------------------------------------------------------

Spawner::~Spawner()
{
    delete timerGunDrop;
    delete timerBuffDrop;
}

void Spawner::Generate(){
    if (timerGunDrop->Elapsed(delayGun) && SpawnRegistry::boxAliveCount() < MAX_SPAWN) {
        
        std::uniform_int_distribution<int> range(0, 3);

        std::uniform_int_distribution<int> rangeNextDelay(delayGun, delayGun * 2);

        std::uniform_int_distribution<int> rangeSurface(0, spawnSurfaces.size() - 1);

        this->delayGun = rangeNextDelay(mt);

        SpawnSurface surface = spawnSurfaces.at(rangeSurface(mt));

        std::uniform_int_distribution<int> rangeX(surface.xi, surface.xf);

        GunBox * gb = new GunBox(GunType(range(mt)), rangeX(mt), surface.y);
        SpawnRegistry::registerBox(gb);
        GravityGuy::actualScene->Add(gb, MOVING);
        
        timerGunDrop->Reset();
    }
    if (timerBuffDrop->Elapsed(delayBuff) && SpawnRegistry::buffAliveCount() < MAX_SPAWN) {

        std::uniform_int_distribution<int> range(1, 3);

        std::uniform_int_distribution<int> rangeNextDelay(delayBuff, delayBuff * 2);

        std::uniform_int_distribution<int> rangeSurface(0, spawnSurfaces.size() - 1);

        this->delayBuff = rangeNextDelay(mt);

        SpawnSurface surface = spawnSurfaces.at(rangeSurface(mt));

        std::uniform_int_distribution<int> rangeX(surface.xi, surface.xf);

        Buff* b = new Buff(BuffType(range(mt)), rangeX(mt), surface.y);
        
        SpawnRegistry::registerBuff(b);

        GravityGuy::actualScene->Add(b, MOVING);

        timerBuffDrop->Reset();
    }
}