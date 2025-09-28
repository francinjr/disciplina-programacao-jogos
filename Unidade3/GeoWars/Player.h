/**********************************************************************************
// Player (Arquivo de Cabe�alho)
//
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define a classe jogador
//
**********************************************************************************/

#ifndef _GEOWARS_PLAYER_H_
#define _GEOWARS_PLAYER_H_

// ---------------------------------------------------------------------------------

#include "Object.h"                        // objetos do jogo
#include "Sprite.h"                        // desenho de sprites
#include "Vector.h"                        // representa��o de vetores
#include "Controller.h"
#include "Animation.h"

// ---------------------------------------------------------------------------------
enum PlayerState {
    RIGHT, LEFT, UP, DOWN, HURT_RIGHT, HURT_LEFT, HURT_UP, HURT_DOWN, IDLE_RIGHT, IDLE_LEFT, IDLE_UP, IDLE_DOWN
};


class Player : public Object
{
private:
    TileSet* tileset;                   // folha de sprites
    Animation* anim;                    // animacao
    Controller* gamepad = nullptr;     // controle de jogo

    PlayerState state = DOWN;
    bool xboxOn = false;
    bool controllerOn = false;
    int health;
    float damageCooldown; // Adicionado: controla o tempo de invencibilidade
    float soundCooldown;

public:
    Vector* speed;                     // velocidade e dire��o

    Player();                           // construtor
    ~Player();                          // destrutor

    void OnCollision(Object* obj);
    void Update();                      // atualiza��o
    void Draw();                        // desenho
    void TakeDamage(int damage);
    int Health() const; // Fun��o para ler a vida
};
// ---------------------------------------------------------------------------------

#endif