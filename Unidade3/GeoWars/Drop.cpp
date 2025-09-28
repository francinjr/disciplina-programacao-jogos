
#include "GeoWars.h"
#include "Drop.h"

// ---------------------------------------------------------------------------------

Drop::Drop(float posX, float posY, TypeOfDrop dropType)
{
    uint normal[1];
    switch (dropType) {
        case PISTOL:
            tileset = new TileSet("Resources/Pistol.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 0;

            break;
        case KNIFE:
            tileset = new TileSet("Resources/Knife.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 0;

            break;
        case SHOTGUN:
            tileset = new TileSet("Resources/Shotgun.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 0;

            break;
        case MEDIC_KIT:
            tileset = new TileSet("Resources/Items.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 0;

            break;
        case GRENADE:
            tileset = new TileSet("Resources/Granade.png", 1, 8);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 0;
            break;
        case AMMO_SMALL:
            tileset = new TileSet("Resources/Items.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 2;
            break;
        case AMMO_MEDIUM:
            tileset = new TileSet("Resources/Items.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 3;
            break;
        case AMMO_BIG:
            tileset = new TileSet("Resources/Items.png", 1, 5);
            anim = new Animation(tileset, 0.120f, true);

            normal[0] = 4;
            break;
     };
    

    anim->Add(0, normal, 1);
    anim->Select(0);


    BBox(new Rect(-10.0f, -10.0f, 10.0f, 10.0f));

    MoveTo(posX, posY);

    this->dropType = dropType;

    type = DROP;
}

// ---------------------------------------------------------------------------------
void Drop::OnCollision(Object* obj) {
    
}

void Drop::Draw() {
    anim->Draw(x, y, Layer::MIDDLE, 1.0f);
}

void Drop::Update() {
    anim->NextFrame();
}

TypeOfDrop Drop::getDropType() {
    return this->dropType;
}

Drop::~Drop()
{
    delete tileset;
    delete anim;
}