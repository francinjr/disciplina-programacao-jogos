/**********************************************************************************
// Enemy (Arquivo de Cabe�alho)
// 
// Cria��o:     19 Dez 2012
// Atualiza��o: 19 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descri��o:   Inimigos do jogo Frogger
//
**********************************************************************************/

#ifndef _FROGGER_ENEMY_H_
#define _FROGGER_ENEMY_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"            // tipos espec�ficos da engine
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
// Fun��es Membro Inline

inline void Enemy::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif