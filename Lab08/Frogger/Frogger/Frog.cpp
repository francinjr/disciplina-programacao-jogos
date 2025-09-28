/**********************************************************************************
// Frog (C�digo Fonte)
// 
// Cria��o:     19 Dez 2012
// Atualiza��o: 19 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define o objeto Sapo no jogo Frogger
//
**********************************************************************************/

#include "Frog.h"

// ---------------------------------------------------------------------------------

Frog::Frog()
{
    // carrega imagem em um sprite
    sprite = new Sprite("Resources/frog.png");

    // posi��o inicial do sapo
    MoveTo(window->CenterX(), 560.0f, Layer::FRONT);
}

// ---------------------------------------------------------------------------------

Frog::~Frog()
{
    delete sprite;
}

// ---------------------------------------------------------------------------------

void Frog::Update()
{
    // desloca sapo para cima
    if (window->KeyPress(VK_UP))
        Translate(0.0f, -40.0f);

    // desloca sapo para baixo
    if (window->KeyPress(VK_DOWN))
        Translate(0.0f, 40.0f);

    // mant�m sapo dentro da tela
    if (y < 80)
        MoveTo(x, 80);
    if (y > 560)
        MoveTo(x, 560);
}

// ---------------------------------------------------------------------------------
