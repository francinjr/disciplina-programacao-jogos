
#include "Bullet.h"
#include "GravityGuy.h"

// ---------------------------------------------------------------------------------

Bullet::Bullet(Image* img, int side, float damage)
{
    // side == 1 é para direita e == -1 é para a esquerda
    sprite = new Sprite(img);
    vel = 250 * side;
    this->damage = damage;
    BBox(new Rect(
        -1.0f * sprite->Width() / 2.0f,
        -1.0f * sprite->Height() / 2.0f,
        sprite->Width() / 2.0f,
        sprite->Height() / 2.0f));

    type = BULLET;
}

// ---------------------------------------------------------------------------------

Bullet::~Bullet()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

float Bullet::getDamage() 
{
    return damage;
}

void Bullet::Update()
{
    // a bala se move apenas no eixo x
    Translate(vel * gameTime, 0);

    if (x > window->Width() || x < 0)
        GravityGuy::actualScene->Delete();
}

// ---------------------------------------------------------------------------------
