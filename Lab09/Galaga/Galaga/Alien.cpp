/**********************************************************************************
// Alien (Arquivo de Cabeçalho)
// 
// Criação:     21 Dez 2012
// Atualização: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Alienígena do jogo Galaga
//
**********************************************************************************/

#include "Alien.h"

// ---------------------------------------------------------------------------------

Alien::Alien(string filename)
{
    sprite = new Sprite(filename);
    vel = 80.0f;
}

// ---------------------------------------------------------------------------------

Alien::~Alien()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Alien::Update()
{
    // desloca alien
    Translate(vel * gameTime, 0.0f);

    // alien saindo pela esquerda
    if (x + sprite->Width()/2.0f < 0)
        MoveTo(window->Width() + sprite->Width()/2.0f, y);

    // alien saindo pela direita
    if (x - sprite->Width()/2.0f > window->Width())
        MoveTo(-sprite->Width()/2.0f, y);
}

// ---------------------------------------------------------------------------------
