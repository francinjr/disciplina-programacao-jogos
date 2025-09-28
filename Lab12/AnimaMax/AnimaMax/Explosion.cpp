/**********************************************************************************
// Explosion (C�digo Fonte)
//
// Cria��o:     20 Jan 2013
// Atualiza��o: 07 Mar 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Anima��o de uma explos�o
//
**********************************************************************************/

#include "Explosion.h"
#include "AnimaMax.h"

// ---------------------------------------------------------------------------------

Explosion::Explosion(TileSet * tiles)
{
    anim = new Animation(tiles, 0.060f, false);
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
        AnimaMax::scene->Delete();
}

// ---------------------------------------------------------------------------------