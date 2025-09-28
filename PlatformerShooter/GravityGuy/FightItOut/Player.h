/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     20 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador 
//
**********************************************************************************/

#ifndef _GRAVITYGUY_PLAYER_H_
#define _GRAVITYGUY_PLAYER_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"                      // tipos espec�ficos da engine
#include "Object.h"                     // interface de Object
#include "Animation.h"                  // anima��o de sprites
#include "TileSet.h"
#include "Gun.h"
#include "Buff.h"
#include <vector>
// ------------------------------------------------------------------------------

enum State {RIGHT, LEFT, IDLE};         // tipo da gravidade
enum PlayerNumber {FIRST, SECOND};


// ---------------------------------------------------------------------------------

class Player : public Object
{
private:
    TileSet* tileset;                // folha de sprites do personagem
    Animation* anim;                   // anima��o do personagem
    Gun* gun = nullptr;
    int speedX;
    int speedY;
    PlayerNumber playerNumber;
    State state;
    int damage;
    int knockback;
    int knockbackSignal;
    int consecutiveJumps = 0; // pode ser trocado para bool com algum refatoramento
    Object* ignoreObj = nullptr;
    std::unordered_map<BuffType, int> playerBuffs;
public:
    Player(PlayerNumber pn);                           // construtor
    ~Player();                          // destrutor

    void Reset();                       // volta ao estado inicial
    float Bottom();                     // coordenadas da base
    float Top();                        // coordenadas do topo
    float Left();
    float Right();
    State getState();
    Gun* GetGun();
    PlayerNumber getPlayerNumber();
    void OnCollision(Object * obj);     // resolu��o da colis�o
    void Update();                      // atualiza��o do objeto
    void Draw();                        // desenho do objeto
};

// ---------------------------------------------------------------------------------
// Fun��o Membro Inline

inline float Player::Bottom()
{
    return y + (tileset->TileHeight() / 2.0);
}

inline float Player::Top()
{
    return y - (tileset->TileHeight() / 2.0);
}
inline float Player::Left()
{
    return x - (tileset->TileWidth() / 2.0);
}

inline float Player::Right()
{
    return x + (tileset->TileWidth() / 2.0);
}

inline State Player::getState()
{
    return state;
}

inline void Player::Draw()
{
    anim->Draw(x, y, z); 
    gun->Draw();
}
inline Gun* Player::GetGun() {
    return gun;
}
// ---------------------------------------------------------------------------------

#endif