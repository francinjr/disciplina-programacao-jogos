/**********************************************************************************
// Missile (C�digo Fonte)
// 
// Cria��o:     23 Nov 2011
// Atualiza��o: 20 Set 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para um m�ssil/proj�til
//
**********************************************************************************/

#include "Missile.h"
#include "Inertia.h"
#include "Explosion.h"
#include "Ship.h"

// ------------------------------------------------------------------------------

Missile::Missile(Ship * ship)
{
    // cria sprite
    sprite = new Sprite("Resources/Missile.png");

    // bounding box
    BBox(new Point());

    // inicializa velocidade
    speed.RotateTo(ship->direction.Angle());
    speed.ScaleTo(10.0f);
    
    // posi��o inicial do m�ssil
    MoveTo(ship->X() + 20 * cos(speed.Radians()), ship->Y() - 20 * sin(speed.Radians()));

    // rota��o do m�ssil
    RotateTo(ship->Rotation());
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::Update()
{
    // deslocamento padr�o
    float deltaT = 50 * gameTime;

    // move m�ssel usando o vetor
    Translate(speed.XComponent() * deltaT, -speed.YComponent() * deltaT);
    
    // destr�i m�ssil que sa� da tela
    if (x > window->Width() || x < 0 || y > window->Height() || y < 0)
    {
        if (rebound)
        {
            Inertia::audio->Play(EXPLOSION);
            Explosion* explo = new Explosion(Inertia::exploSet);
            explo->MoveTo(x, y);
            Inertia::scene->Add(explo, STATIC);
            Inertia::scene->Delete();
        }
        else
        {

            Vector* v = new Vector(ang, mag);
            rebound = false;
        }
    }
}

// -------------------------------------------------------------------------------

void Missile::Draw()
{
    sprite->Draw(x, y, z, scale, rotation);
}

// -------------------------------------------------------------------------------
