
#include "MidnightRunner.h"
#include "Enemy.h"
#include "Road.h"
#include "Level1.h"
Enemy::Enemy(float positionX, float positionY, TypeOfEnemy typeOfEnemy, Image * img)
{
    sprite = new Sprite(img);

    switch (typeOfEnemy)
    {
        case HATCH:
            speed = 650;
            break;
        case SEDAN:
            speed = 700;
            break;
        case SMALL_TRUCK:
            speed = 500;
            break;
        case BIG_TRUCK:
            speed = 400;
            break;
        default:
            speed = 500; // Default speed for unknown enemy types
            break;
	}


    BBox(new Rect((-sprite->Width()  / 2.0f) + 8.0f,      // X1
                  (-sprite->Height() / 2.0f) + 8.0f,      // Y1
                   (sprite->Width()  / 2.0f) - 8.0f,      // X2
                   (sprite->Height() / 2.0f) - 8.0f)      // Y2
    );

    MoveTo(positionX, positionY);
    
    if (X() < window->CenterX() - 75.0f)
        speed = speed * 1.2f; // Aumenta a velocidade se o carro estiver na parte esquerda da tela
    else if (X() > window->CenterX() + 75.0f)
		speed = speed * 0.8f; // Diminui a velocidade se o carro estiver na parte direita da tela
    
    type = TRAFFIC;
}

Enemy::~Enemy()
{
    delete sprite;
}

void Enemy::OnCollision(Object * obj)
{
    if (obj->Type() == TRAFFIC) {
        Enemy* enemy = (Enemy *) obj;
        if (obj->Y() < Y()) {
            // se o objeto que colidiu estiver acima desse objeto
            obj->MoveTo(obj->X(), Y() - (sprite->Height() / 2.0f) - (enemy->sprite->Height() / 2.0f));
            speed = speed > enemy->speed ? enemy->speed : speed;
        }
   }
}

void Enemy::Update()
{
    // Problema: A velocidade de um carro indo em direção ao outro deve ser (em movimento) deve ser maior do que quando o segundo carro estiver em repouso.
    
    if (Road::isEnding())
	{
        Translate(0, -speed  * gameTime);

        if (Y() < 0 - (sprite->Height() / 2)) Level1::scene->Delete();
	}
    else
        Translate(0, (-speed + Road::globalVel) * gameTime);

    if (Y() > window->Height() + (sprite->Height() / 2)) 
        Level1::scene->Delete(); // deletar objeto ao sair da cena    
}


void Enemy::Draw()
{
    sprite->Draw(x, y, Layer::LOWER);
}
