/**********************************************************************************
// Player (C�digo Fonte)
// 
// Cria��o:     20 Abr 2012
// Atualiza��o: 12 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para o jogador
//
**********************************************************************************/

#include "Player.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
    anim
        = new Animation(tileset, 0.120f, true);
    MoveTo(window->CenterX(), 24.0f, 0.0f);

}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    
}

// ---------------------------------------------------------------------------------

void Player::OnCollision(Object * obj)
{
    // jogador s� pode alterar a gravidade enquanto estiver 
    // em cima de uma plataforma, n�o � poss�vel a mudan�a no ar 
    if (window->KeyPress(VK_SPACE))
    {
        gravity = !gravity;
    }
    // tira player da plataforma para evitar  
    // detec��o de colis�o no quadro seguinte 
    if (gravity == NORMAL)
        Translate(0, 12);
    else
        Translate(0, -12);
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    tileset = new TileSet("Resources/GravityGuy.png", 32, 48, 5, 10);
    anim
        = new Animation(tileset, 0.120f, true);
    MoveTo(window->CenterX(), 24.0f, 0.0f);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    anim->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
