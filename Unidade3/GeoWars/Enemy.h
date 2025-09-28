/**********************************************************************************
// Blue (Arquivo de Cabe�alho)
//
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Objeto faz uma persegui��o suavizada
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

    Vector* speed;                     // velocidade e dire��o
    int life;

    float baseSpeed;
    Player* player;

    bool chase = 0;
public:
    Enemy(Player* player, int life, Vector* speed);
    ~Enemy();


    virtual void OnCollision(Object* obj) = 0;      // resolu��o da colis�o
    virtual void OnAgroCollision(Object* obj) = 0;      // resolu��o da colis�o
    virtual void Update() = 0;                      // atualiza��o
    virtual void Draw() = 0;                        // desenho
    virtual void TakeDamage(int damage);
};


#endif