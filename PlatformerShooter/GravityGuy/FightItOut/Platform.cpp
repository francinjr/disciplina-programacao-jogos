/**********************************************************************************
// Platform (C�digo Fonte)
// 
// Cria��o:     21 Abr 2012
// Atualiza��o: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Plataformas do jogo
//
**********************************************************************************/

#include "Platform.h"
#include "GravityGuy.h"
// ---------------------------------------------------------------------------------

Platform::Platform(float posX, float posY, Color tint, Sprite * sprite) : color(tint)
{
   
     platform = sprite;
     type = PLATFORM;
     
    BBox(new Rect(-platform->Width()/2.0f, 
        (-platform->Height() / 2.0f),
                   platform->Width()/2.0f, 
        (platform->Height() / 2.0f)));
    height = platform->Height();

    MoveTo(posX, posY, Layer::MIDDLE);
}

// ---------------------------------------------------------------------------------

Platform::~Platform()
{
    delete platform;
}

// -------------------------------------------------------------------------------

void Platform::Update()
{
    
}

// -------------------------------------------------------------------------------
