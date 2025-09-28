
#include "GeoWars.h"
#include "Box.h"

// ---------------------------------------------------------------------------------

Box::Box(float posX, float posY, TypeOfDrop typeOfDrop)
{
    // temporario
    tileset = new TileSet("Resources/Box.png", 20, 10, 1, 1);
    anim = new Animation(tileset, 0.120f, true);

    uint normal[1] = { 0 };
    uint broken[4] = { 0,1,2,3 };

    anim->Add(NORMAL, normal, 1);
    anim->Add(BROKEN, broken, 4);

    BBox(new Rect(-10.0f, -10.0f, 10.0f, 10.0f));

    MoveTo(posX, posY);

    this->typeOfDrop = typeOfDrop;

    anim->Select(NORMAL);

    type = BOX;
}

// ---------------------------------------------------------------------------------
void Box::OnCollision(Object* obj) {
    // depois tem que alterar... do jeito que está, apenas batendo a caixa se quebra, mas eu quero que ela se quebre somnete no atack. Esperando terminarem a parte do atack
    if (obj->Type() == PLAYER) {
        // � destruida
        if(this->typeOfDrop != EMPTY)
            GeoWars::scene->Add(new Drop(X(), Y(), this->typeOfDrop), STATIC);

        GeoWars::scene->Delete(this, STATIC);
    }
}

void Box::Draw() {
    anim->Draw(x, y, Layer::MIDDLE, 1.0f);
}

void Box::Update() {
    anim->NextFrame();
}

Box::~Box()
{
    delete tileset;
    delete anim;
}