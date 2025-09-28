/**********************************************************************************
// Enemy (C�digo Fonte)
// 
// Cria��o:     19 Dez 2012
// Atualiza��o: 19 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descri��o:   Inimigos do jogo Frogger
//
**********************************************************************************/

#include "Enemy.h"

// ---------------------------------------------------------------------------------

Enemy::Enemy(Image * img, float speed)
{
    sprite = new Sprite(img);
    vel    = speed;
}

// ---------------------------------------------------------------------------------

Enemy::~Enemy()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Enemy::Update()
{
    // desloca objeto no eixo x
    Translate(-vel * gameTime, 0.0f);
    
    // passa objeto de um lado da tela para o outro
    if (x + sprite->Width() / 2.0f < 0)
        MoveTo(window->Width() + sprite->Width() / 2.0f, y);
}

// ---------------------------------------------------------------------------------
