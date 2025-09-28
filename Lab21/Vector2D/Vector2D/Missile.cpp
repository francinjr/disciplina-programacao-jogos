/**********************************************************************************
// Missile (C�digo Fonte)
// 
// Cria��o:     23 Nov 2011
// Atualiza��o: 18 Set 2023
// Compilador:  Visual C++ 2012
//
// Descri��o:   Define uma classe para um m�ssil/proj�til
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
    
    // usa mesma rota��o do avi�o
    RotateTo(plane->Rotation());
    
    // move para posi��o
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
    // desloca m�ssil pelas componentes do vetor speed
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);
    
    // se o m�ssil sair da janela
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
