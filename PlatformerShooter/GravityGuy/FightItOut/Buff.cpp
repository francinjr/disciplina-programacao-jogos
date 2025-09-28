
#include "Buff.h"
#include "GravityGuy.h"
// ---------------------------------------------------------------------------------

Buff::Buff(BuffType buff, float finalX, float finalY)
{
    this->buffType = buff;
    switch (buff) {
    case HEAL: {
        tileset = new TileSet("Resources/buffs-1.png", 24, 24, 2, 4);
        uint seq[1] = { 0 };
        anim = new Animation(tileset, 0.06f, true);
        anim->Add(0, seq, 1);
        break;
    }
    case RAPID_FIRE: {
        tileset = new TileSet("Resources/buffs-1.png", 24, 24, 2, 4);
        uint seq[1] = { 1 };
        anim = new Animation(tileset, 0.06f, true);
        anim->Add(0, seq, 1);
        break;
    }
    case SHIELD: {
        tileset = new TileSet("Resources/buffs-1.png", 24, 24, 2, 4);
        uint seq[1] = { 2 };
        anim = new Animation(tileset, 0.06f, true);
        anim->Add(0, seq, 1);
        break;
    }
    case EXTRA_DAMAGE: {
        tileset = new TileSet("Resources/buffs-1.png", 24, 24, 2, 4);
        uint seq[1] = { 3 };
        anim = new Animation(tileset, 0.06f, true);
        anim->Add(0, seq, 1);
        break;
    }
    }


    type = BUFF;

    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));

    MoveTo(finalX, finalY - (tileset->TileHeight() / 2.0f), Layer::UPPER);
    timer = new Timer();
    timer->Start();
}

// ---------------------------------------------------------------------------------

Buff::~Buff()
{
    delete tileset;
    delete anim;
}



void Buff::Update()
{
    anim->Select(0);
    anim->NextFrame();
}

void Buff::Draw()
{
    anim->Draw(X(), Y());
}
// -------------------------------------------------------------------------------
