/**********************************************************************************
// Player (Arquivo de Cabe�alho)
// 
// Cria��o:     21 Dez 2012
// Atualiza��o: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Player do jogo Galaga
//
**********************************************************************************/

#include "Player.h"
#include "Missile.h"
#include "Galaga.h"

// ---------------------------------------------------------------------------------

Player::Player()
{
    sprite  = new Sprite("Resources/Nave.png");
    missile = new Image ("Resources/Missile.png");

    MoveTo(window->CenterX(), window->Height() - 30.0f, Layer::FRONT);
    vel = 160;
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete sprite;
    delete missile;
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    // dispara um m�ssil com a barra de espa�o
    if (window->KeyPress(VK_SPACE))
    {
        // tamanho do m�ssel � 26x30
        Missile * m = new Missile(missile);
        m->MoveTo(x, y - sprite->Height()/2.0f, Layer::UPPER);
        Galaga::scene->Add(m);
    }

    // desloca nave horizontalmente
    if (window->KeyDown(VK_RIGHT))
        Translate(vel * gameTime, 0);
    if (window->KeyDown(VK_LEFT))
        Translate(-vel * gameTime, 0);

    // mant�m nave dentro da janela
    if (x - sprite->Width()/2.0f < 0)
        MoveTo(sprite->Width()/2.0f, y);
    if (x + sprite->Width()/2.0f > window->Width())
        MoveTo(window->Width() - sprite->Width()/2.0f, y);
}

// ---------------------------------------------------------------------------------
