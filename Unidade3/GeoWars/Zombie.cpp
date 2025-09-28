
#include "GeoWars.h"
#include "Zombie.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------

Zombie::Zombie(Player* p, int life, Vector* speed) : Enemy(p, life, speed), angle(0, 359), secs(3.0f, 5.0f)
{
    baseSpeed = 50.0f;
    tileset = new TileSet("Resources/Zombie_Medium.png", 68, 68, 7, 28);
    anim = new Animation(tileset, 0.120f, true);

    // sequencias de animação
    uint walkUp[4] = { 21,22,23,24 };
    uint walkDown[4] = { 0,1,2,3 };
    uint walkLeft[4] = { 7,8,9,10 };
    uint walkRight[4] = { 14,15,16,17 };

    uint leftDamaged[3] = { 11,12,13 };
    uint rightDamaged[3] = { 18,19,20 };
    uint downDamaged[3] = { 4,5,6 };
    uint upDamaged[3] = { 25,26,27 };

    uint idleUp[1] = { 21 };
    uint idleDown[1] = { 0 };
    uint idleLeft[1] = { 7 };
    uint idleRight[1] = { 14 };

    anim->Add(HURT_RIGHT, rightDamaged, 3);
    anim->Add(HURT_LEFT, leftDamaged, 3);
    anim->Add(HURT_UP, upDamaged, 3);
    anim->Add(HURT_DOWN, downDamaged, 3);

    anim->Add(RIGHT, walkRight, 4);
    anim->Add(LEFT, walkLeft, 4);
    anim->Add(UP, walkUp, 4);
    anim->Add(DOWN, walkDown, 4);

    anim->Add(IDLE_UP, idleUp, 1);
    anim->Add(IDLE_DOWN, idleDown, 1);
    anim->Add(IDLE_LEFT, idleLeft, 1);
    anim->Add(IDLE_RIGHT, idleRight, 1);

    BBox(new Circle(18.0f));
    Agro(new Circle(150.0f));

    MoveTo(window->CenterX(), window->CenterY());

    timer = new Timer();
    timer->Start();

    anim->Select(UP);

    NewDirection();

    type = ENEMY;
}

// ---------------------------------------------------------------------------------

Zombie::~Zombie()
{
    delete tileset;
    delete anim;
}

void Zombie::OnCollision(Object* obj) {
    if (obj->Type() == MAPWALL) {
        speed->RotateTo(speed->Angle() + 180);
        Translate(speed->XComponent() * 200.0f * gameTime, -speed->YComponent() * 200.0f * gameTime);
        NewDirection(Random(speed->Angle() - 30, speed->Angle() + 30));
        ChooseAnimation();
    }
}
void Zombie::OnAgroCollision(Object* obj) {

    if (obj->Type() == PLAYER) {
        chase = true;
    }
}
void Zombie::NewDirection(Random<float> randomAngle)
{
    // nova direção aleatória
    speed->RotateTo(randomAngle.Rand());

    // tempo aleatório
    delay = secs.Rand();

    // inicia medição do tempo
    timer->Start();
}
void Zombie::NewDirection()
{
    // nova direção aleatória
    speed->RotateTo(angle.Rand());

    // tempo aleatório
    delay = secs.Rand();

    // inicia medição do tempo
    timer->Start();
}


void Zombie::Update() {


    if (chase) {
        // ajusta ângulo do vetor 
        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        baseSpeed = 65.0f;
    }
    else {
        if (timer->Elapsed(delay)) NewDirection();
        baseSpeed = 50.0f;
    }

    // tem que fazer código para não permitir sair do mapa, pode ser feito em collision

    ChooseAnimation();

    Translate(speed->XComponent() * baseSpeed * gameTime, -speed->YComponent() * baseSpeed * gameTime);
    if (x < 10 || x < 10 || x > game->Width() - 10 || y > game->Height() - 10) NewDirection();
    ChooseAnimation();
    chase = false;
    anim->NextFrame();
}

void Zombie::ChooseAnimation() {
    if (speed->Angle() >= 320.0f || speed->Angle() < 75.0f) {
        anim->Select(RIGHT);
    }
    else if (speed->Angle() >= 75.0f && speed->Angle() < 150.0f) {
        anim->Select(UP);
    }
    else if (speed->Angle() >= 150.0f && speed->Angle() < 240.0f) {
        anim->Select(LEFT);
    }
    else anim->Select(DOWN);
}

void Zombie::Draw() {
    anim->Draw(x, y);
}