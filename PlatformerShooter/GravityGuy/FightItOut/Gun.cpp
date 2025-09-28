
#include "Gun.h"
#include "GravityGuy.h"
#include "Bullet.h"
// ---------------------------------------------------------------------------------

Gun::Gun(int posX, int posY,GunType gunType, int pn)
{
    playerNumber = pn;
    switch (gunType) {
    case PISTOL: {
        ammo = 10;
        fireRating = 0.65;
        damage = 13.5;
        gunTileSet = new TileSet("Resources/guns_animations/Glock.png", 32, 24, 12, 12);
        uint shootRightSequence[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
        uint idleRightSequence[1] = { 1 };
        uint shootLeftSequence[11] = { 13,14,15,16,17,18,19,20,21,22,23 };
        uint idleLeftSequence[1] = { 12 };
        anim = new Animation(gunTileSet, 0.06f, true);
        anim->Add(AIM_RIGHT, idleRightSequence, 1);
        anim->Add(SHOOT_RIGHT, shootRightSequence, 11);
        anim->Add(AIM_LEFT, idleLeftSequence, 1);
        anim->Add(SHOOT_LEFT, shootLeftSequence, 11);
        break;
    }
    case SMG: {
        ammo = 30;
        fireRating = 0.2;
        damage = 23;
        gunTileSet = new TileSet("Resources/guns_animations/SMG.png", 40, 24, 12, 12);
        uint shootRightSequence[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
        uint idleRightSequence[1] = { 1 };
        uint shootLeftSequence[11] = { 13,14,15,16,17,18,19,20,21,22,23 };
        uint idleLeftSequence[1] = { 12 };
        anim = new Animation(gunTileSet, 0.06f, true);
        anim->Add(AIM_RIGHT, idleRightSequence, 1);
        anim->Add(SHOOT_RIGHT, shootRightSequence, 11);
        anim->Add(AIM_LEFT, idleLeftSequence, 1);
        anim->Add(SHOOT_LEFT, shootLeftSequence, 11);
        break;
    }
    case RIFLE: {
        ammo = 30;
        fireRating = 0.32;
        damage = 30;
        gunTileSet = new TileSet("Resources/guns_animations/Ak.png", 48, 24, 12, 24);
        uint shootRightSequence[11] = { 1,2,3,4,5,6,7,8,9,10,11 };
        uint idleRightSequence[1] = { 1 };
        uint shootLeftSequence[11] = { 13,14,15,16,17,18,19,20,21,22,23 };
        uint idleLeftSequence[1] = { 12 };
        anim = new Animation(gunTileSet, 0.06f, true);
        anim->Add(AIM_RIGHT, idleRightSequence, 1);
        anim->Add(SHOOT_RIGHT, shootRightSequence, 11);
        anim->Add(AIM_LEFT, idleLeftSequence, 1);
        anim->Add(SHOOT_LEFT, shootLeftSequence, 11);
        break;
    }
    case REVOLVER: {
        ammo = 7;
        fireRating = 0.8;
        damage = 42;
        gunTileSet = new TileSet("Resources/guns_animations/Revolver.png", 32, 16, 10, 20);
        uint shootRightSequence[10] = { 1,2,3,4,5,6,7,8,9 };
        uint idleRightSequence[1] = { 1 };
        uint shootLeftSequence[10] = { 11,12,13,14,15,16,17,18,19 };
        uint idleLeftSequence[1] = { 10 };
        anim = new Animation(gunTileSet, 0.06f, true);
        anim->Add(AIM_RIGHT, idleRightSequence, 1);
        anim->Add(SHOOT_RIGHT, shootRightSequence, 10);
        anim->Add(AIM_LEFT, idleLeftSequence, 1);
        anim->Add(SHOOT_LEFT, shootLeftSequence, 10);;
        break;
    }
    }


    gunState = AIM_RIGHT    ;
    anim->Select(gunState);
    type = GUN;
   
    MoveTo(posX, posY, Layer::UPPER);



    timer = new Timer();
    timer->Start();
}

// ---------------------------------------------------------------------------------

Gun::~Gun()
{
    delete timer;
    delete gunTileSet;
    delete anim;
}

// -------------------------------------------------------------------------------

Bullet* Gun::Shoot() {
    if (timer->Elapsed(fireRating)) {
        int side = 0;
        if (playerNumber == 0)
        {
            side = GravityGuy::player1->getState() == RIGHT ? 1 : -1;
        }
        else {
            side = GravityGuy::player2->getState() == RIGHT ? 1 : -1;
        }
        Bullet* bullet = new Bullet(GravityGuy::bulletImg, side, damage);
        ammo--;
        timer->Reset();
        if (ammo == 0) {
            // remove arma
        }

        return bullet;
    }
    return nullptr;
}

void Gun::changeSide(bool isRight)
{
    // talvez possa ser mudado o método, de forma que o sprite não seja recriado a cada input
    if (isRight) gunState = AIM_RIGHT;
    else gunState = AIM_LEFT;
}

void Gun::Update()
{
    anim->Select(gunState);
    anim->NextFrame();
}

void Gun::Draw()
{
    float posX = 0;
    float posY = 0;
    if (playerNumber == 0)
    {
        if (GravityGuy::player1->getState() == LEFT) posX = GravityGuy::player1->Left() - (gunTileSet->TileWidth() / 5.0f);
        else posX = GravityGuy::player1->Right() + (gunTileSet->TileWidth() / 3.3f);
        posY = GravityGuy::player1->Y() + (gunTileSet->TileHeight() / 4.0f);
    }
    else {
        if (GravityGuy::player2->getState() == LEFT) posX = GravityGuy::player2->Left() - (gunTileSet->TileWidth() / 5.0f);
        else posX = GravityGuy::player2->Right() + (gunTileSet->TileWidth() / 3.3f);
        posY = GravityGuy::player2->Y() + (gunTileSet->TileHeight() / 4.0f);
    }

    anim->Draw(posX, posY);
}
// -------------------------------------------------------------------------------
