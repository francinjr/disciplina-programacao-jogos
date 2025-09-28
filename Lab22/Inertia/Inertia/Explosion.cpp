/**********************************************************************************
// Explosion (Código Fonte)
//
// Criação:     07 Fev 2013
// Atualização: 20 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Animação de uma explosão
//
**********************************************************************************/

#include "Explosion.h"
#include "Inertia.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(TileSet * tiles)
{
    anim = new Animation(tiles, 0.020f, false);
}

// ---------------------------------------------------------------------------------

Explosion::~Explosion()
{
    delete anim;
}

// ---------------------------------------------------------------------------------

void Explosion::Update()
{
    anim->NextFrame();

    if (anim->Inactive())
        Inertia::scene->Delete();    
}

// ---------------------------------------------------------------------------------