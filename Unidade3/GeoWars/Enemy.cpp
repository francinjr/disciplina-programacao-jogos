
#include "GeoWars.h"
#include "Enemy.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Enemy::Enemy(Player* p, int life, Vector* speed) : player(p)
{
    this->speed = speed;
    this->life = life;
    this->player = p;

    BBox(new Circle(20.0f));

    MoveTo(300, 300);

    type = ENEMY;
}

// ---------------------------------------------------------------------------------

Enemy::~Enemy()
{
    delete speed;
}


// Adicione este novo m�todo ao final do arquivo
void Enemy::TakeDamage(int damage)
{
    life -= damage;
}
