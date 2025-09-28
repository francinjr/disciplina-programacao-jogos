#ifndef _MIDNIGHTRUNNER_ENEMY_H_
#define _MIDNIGHTRUNNER_ENEMY_H_

#include "Object.h"
#include "Sprite.h"

enum TypeOfEnemy
{
    SEDAN,
    HATCH,
    SMALL_TRUCK,
    BIG_TRUCK,                                     
};

class Enemy : public Object
{
private:
    Sprite* sprite = nullptr;
    float speed = 350.0f;
public:

    Enemy(float positionX,float positionY, TypeOfEnemy typeOfEnemy, Image * img);
    ~Enemy();

    void OnCollision(Object * obj);
    void Update();
    void Draw();
};

#endif