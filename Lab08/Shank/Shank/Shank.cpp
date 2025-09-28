/**********************************************************************************
// Shank (C�digo Fonte)
//
// Cria��o:     21 Dez 2012
// Atualiza��o: 14 Ago 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define personagem Shank como um objeto do jogo
//
**********************************************************************************/

#include "Shank.h"

// ---------------------------------------------------------------------------------

Shank::Shank()
{
    sprite = new Sprite("Resources/Shank.png");
    MoveTo(380.0f, 348.0f, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Shank::~Shank()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Shank::Update()
{
    if (window->KeyDown(VK_LEFT))
        Translate(-50.0f * gameTime, 0.0f);
    if (window->KeyDown(VK_RIGHT))
        Translate(+50.0f * gameTime, 0.0f);
    if (window->KeyDown(VK_UP))
        Translate(0.0f, -50.0f * gameTime);
    if (window->KeyDown(VK_DOWN))
        Translate(0.0f, +50.0f * gameTime);
}

// ---------------------------------------------------------------------------------

void Shank::Draw()
{
    sprite->Draw(x, y, z);
}

// ---------------------------------------------------------------------------------
