/**********************************************************************************
// Block (Arquivo de Cabe�alho)
// 
// Cria��o:     22 Dez 2012
// Atualiza��o: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Bloco do jogo Breakout
//
**********************************************************************************/

#include "Block.h"
#include "Breakout.h"

// ---------------------------------------------------------------------------------

Block::Block(Image * img)
{
    sprite  = new Sprite(img);
    velX = 0.0f;
    velY = 0.0f;
}

// ---------------------------------------------------------------------------------

Block::~Block()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Block::Update()
{
    // desloca bloco
    Translate(velX * gameTime, velY * gameTime);

    // destr�i ao sair da janela
    if (y - sprite->Height()/2.0f > window->Height())
        Breakout::scene->Delete();
}

// ---------------------------------------------------------------------------------
