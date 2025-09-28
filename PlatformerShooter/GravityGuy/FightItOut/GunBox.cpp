
#include "GunBox.h"
#include "GravityGuy.h"
#include "Platform.h"

// ---------------------------------------------------------------------------------

GunBox::GunBox(GunType gun,float finalX, float finalY)
{
    this->gun = gun;
    type = GUNBOX;

    sprite = new Sprite("Resources/Crate.png");

    BBox(new Rect(-sprite->Width() / 2.0f,
        -sprite->Height() / 2.0f,
        sprite->Width() / 2.0f,
        sprite->Height() / 2.0f));
    
    MoveTo(finalX, 0, Layer::UPPER);
}

// ---------------------------------------------------------------------------------

GunBox::~GunBox()
{
    delete sprite;
}

void GunBox::OnCollision(Object* obj)
{
    if (obj->Type() == PLATFORM && obj->Y() >= finalY) {
        Platform* plat = (Platform*)obj;

        if (Y() <= plat->Top() + 5 && Bottom() <= plat->Y() + 3) {
            // tá em cima
            MoveTo(x, plat->Top() - (sprite->Height() / 2.0f));
            
        }
    }
}
// -------------------------------------------------------------------------------

void GunBox::Update()
{
    // tem que diminuir a gravidade, era bom adicionar um tipo de paraquedas na caixa
    Translate(0, GravityGuy::GRAVITY / 3.0f);
}

void GunBox::Draw()
{
    sprite->Draw(X(), Y(), z, 1.0f, 0.0f);
}
// -------------------------------------------------------------------------------
