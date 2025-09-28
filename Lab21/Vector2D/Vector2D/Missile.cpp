/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:     23 Nov 2011
// Atualização: 18 Set 2023
// Compilador:  Visual C++ 2012
//
// Descrição:   Define uma classe para um míssil/projétil
//
**********************************************************************************/

#include "Missile.h"
#include "Vector2D.h"

// ------------------------------------------------------------------------------

Missile::Missile(Plane * plane, Image * img, int angle, int defasagem)
{
    // inicializa sprite
    sprite = new Sprite(img);

    // inicializa vetor velocidade
    speed.RotateTo(plane->Angle() - angle);
    speed.ScaleTo(500);
    
    // usa mesma rotação do avião
    RotateTo(plane->Rotation());
    
    // move para posição
    //MoveTo(plane->X() + 50 * cos(speed.Radians()), plane->Y() - 50 * sin(speed.Radians()));
    MoveTo(plane->X() + 50 * cos(speed.Radians() + defasagem), plane->Y() - 50 * sin(speed.Radians() + defasagem));
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
    // desloca míssil pelas componentes do vetor speed
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);
    
    // se o míssil sair da janela
    if (x > window->Width() || x < 0 || y > window->Height() || y < 0)
    {
        Vector2D::audio->Play(EXPLOSION);
        Vector2D::scene->Delete();
    }
}

// -------------------------------------------------------------------------------

void Missile::Draw()
{
    sprite->Draw(x, y, z, scale, rotation);
}

// -------------------------------------------------------------------------------
