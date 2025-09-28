/**********************************************************************************
// Enemy (Arquivo de Cabeçalho)
// 
// Criação:     19 Dez 2012
// Atualização: 19 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descrição:   Inimigos do jogo Frogger
//
**********************************************************************************/

#ifndef _FROGGER_ENEMY_H_
#define _FROGGER_ENEMY_H_

// ---------------------------------------------------------------------------------
// Inclusões

#include "Types.h"            // tipos específicos da engine
#include "Object.h"           // interface de object
#include "Sprite.h"           // interface de sprites
#include "Image.h"            // interface de image

// ---------------------------------------------------------------------------------

class Enemy : public Object
{
private:
    Sprite * sprite;
    float vel;

public:
    Enemy(Image * img, float speed);
    ~Enemy();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Funções Membro Inline

inline void Enemy::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif