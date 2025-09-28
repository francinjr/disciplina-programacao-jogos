#ifndef _MIDNIGHTRUNNER_PLAYER_H_
#define _MIDNIGHTRUNNER_PLAYER_H_

#include <cmath>
#include "Object.h"
#include "Sprite.h"

class Player : public Object
{
private:
    Sprite* player = nullptr;
    Sprite* lifeImage = nullptr;
    float iniPos;
    int lifeCount;

public:

    Player();
    ~Player();

    int GetLifeCount() const { return lifeCount; }

    void OnCollision(Object* obj);
    void Update();
    void Draw();
};

#endif