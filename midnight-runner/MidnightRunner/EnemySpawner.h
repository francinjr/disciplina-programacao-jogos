#ifndef _MIDNIGHTRUNNER_ENEMYSPAWNER_H_
#define _MIDNIGHTRUNNER_ENEMYSPAWNER_H_

#include "Scene.h"
#include "Timer.h"
#include <unordered_map>
#include "Enemy.h"
#include "Road.h"

class EnemySpawner
{
private:
    Scene* scene = nullptr;
    Timer * timer = nullptr;
    float SPAWN_DELAY;
    std::unordered_map<TypeOfEnemy, Image*> imgs;
public:
    EnemySpawner(Scene* newScene);
    ~EnemySpawner();

    void InitPatterns();
    void GenerateEnemies();
    int GetLaneX(int lane);

};



#endif