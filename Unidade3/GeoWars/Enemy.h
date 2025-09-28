/**********************************************************************************
// Blue (Arquivo de Cabeçalho)
//
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto faz uma perseguição suavizada
//
**********************************************************************************/

#ifndef _GEOWARS_ENEMY_H_
#define _GEOWARS_ENEMY_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"
#include "Random.h"

// ---------------------------------------------------------------------------------

class Enemy : public Object
{
protected:
    TileSet* tileset = nullptr;                   // folha de sprites
    Animation* anim = nullptr;                    // animacao

    Vector* speed;                     // velocidade e direção
    int life;

    float baseSpeed;
    Player* player;

    bool chase = 0;
public:
    Enemy(Player* player, int life, Vector* speed);
    ~Enemy();


    virtual void OnCollision(Object* obj) = 0;      // resolução da colisão
    virtual void OnAgroCollision(Object* obj) = 0;      // resolução da colisão
    virtual void Update() = 0;                      // atualização
    virtual void Draw() = 0;                        // desenho
    virtual void TakeDamage(int damage);
};


#endif