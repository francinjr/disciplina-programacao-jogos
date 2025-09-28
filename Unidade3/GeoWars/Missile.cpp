/**********************************************************************************
// Missile (C�digo Fonte)
//
// Cria��o:     23 Nov 2011
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Define uma classe para um m�ssil
//
**********************************************************************************/

#include "Missile.h"
#include "WallHit.h"
#include "GeoWars.h"
#include "Enemy.h"

// ------------------------------------------------------------------------------

Player*& Missile::player = GeoWars::player;

// ------------------------------------------------------------------------------

Missile::Missile()
{
    sprite = new Sprite("Resources/Missile.png");
    BBox(new Circle(8));

    speed.RotateTo(player->speed->Angle());
    // CORRE��O: Aumentamos a velocidade base para ser r�pida por padr�o
    speed.ScaleTo(800.0f);

    MoveTo(player->X() + 22 * cos(speed.Radians()), player->Y() - 22 * sin(speed.Radians()));
    RotateTo(-player->speed->Angle() + 90.0f);

    type = MISSILE;
}

// ------------------------------------------------------------------------------

Missile::~Missile()
{
    delete sprite;
}

// -------------------------------------------------------------------------------

void Missile::OnCollision(Object* obj)
{
    if (obj->Type() == ENEMY)
    {
        Enemy* enemy = (Enemy*)obj;
        enemy->TakeDamage(damage);

        // Som da explos�o
        //GeoWars::audio->Play(EXPLODE);
        GeoWars::scene->Delete(this, MOVING);
    }
}

void Missile::Update()
{
    // CORRE��O: Movimento agora � uniforme em todas as dire��es, sem multiplicadores extras
    Translate(speed.XComponent() * gameTime, -speed.YComponent() * gameTime);

    if (x > game->Width() - 50 || x < 50 || y > game->Height() - 50 || y < 50)
    {
        float distance = Point::Distance(Point(x, y), Point(player->X(), player->Y()));
        float level = (MaxDistance - distance) / MaxDistance * BaseVolume;
        GeoWars::audio->Volume(HITWALL, level);
        GeoWars::audio->Play(HITWALL);

        GeoWars::scene->Add(new WallHit(x, y), STATIC);
        GeoWars::scene->Delete(this, MOVING);
    }
}

// -------------------------------------------------------------------------------