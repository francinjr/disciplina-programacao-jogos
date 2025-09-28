#pragma once
#ifndef _GRAVITYGUY_SPAWNREGISTRY_H_
#define _GRAVITYGUY_SPAWNREGISTRY_H_

#include <algorithm>
#include <vector>
#include "GunBox.h"
#include "Buff.h"

class SpawnRegistry {
public:
    static void registerBox(GunBox* g) {
        boxes.push_back(g);
    }
    static void unregisterBox(GunBox* g) {
        boxes.erase(std::remove(boxes.begin(), boxes.end(), g), boxes.end());
    }
    static int  boxAliveCount() { return (int)boxes.size(); }



    static void registerBuff(Buff* b) {
        buffs.push_back(b);
    }
    static void unregisterBuff(Buff* b) {
        buffs.erase(std::remove(buffs.begin(), buffs.end(), b), buffs.end());
    }
    static int  buffAliveCount() { return (int)buffs.size(); }
private:
    static std::vector<GunBox*> boxes;
    static std::vector<Buff*> buffs;
};
#pragma once

#endif