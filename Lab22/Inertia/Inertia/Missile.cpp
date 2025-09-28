/**********************************************************************************
// Missile (Código Fonte)
// 
// Criação:     23 Nov 2011
// Atualização: 20 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para um míssil/projétil
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
    
    // posição inicial do míssil
    MoveTo(ship->X() + 20 * cos(speed.Radians()), ship->Y() - 20 * sin(speed.Radians()));

    // rotação do míssil
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
    // deslocamento padrão
    float deltaT = 50 * gameTime;

    // move míssel usando o vetor
    Translate(speed.XComponent() * deltaT, -speed.YComponent() * deltaT);
    
    // destrói míssil que saí da tela
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
