
#include "GeoWars.h"
#include "SmallZombie.h"
#include "Random.h" 

// ---------------------------------------------------------------------------------
SmallZombie::SmallZombie(Player* p, int life, Vector* speed) : Enemy(p,life,speed), angle(0, 359), secs(3.0f, 5.0f)
{
    tileset = new TileSet("Resources/Zombie_Small.png", 68, 68, 7, 28);
    anim = new Animation(tileset, 0.120f, true);
    baseSpeed = 65.0f;
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
    Agro(new Circle(220.0f));

    MoveTo(window->CenterX(), window->CenterY());
    
    timer = new Timer();
    timer->Start();

    anim->Select(UP);

    NewDirection();

    type = ENEMY;
}

// ---------------------------------------------------------------------------------

SmallZombie::~SmallZombie()
{
    delete tileset;
    delete anim;
}

void SmallZombie::OnCollision(Object* obj) {
    // se colidir com a parede, deve gerar uma NewDirection, ou pode fazer com que o bixo ande para o lado oposto por um breve tempo antes de gerar direction novamente.
    // Isso só acontece se o chase estiver false.
    if (obj->Type() == MAPWALL) {
        speed->RotateTo(speed->Angle() + 180);
        Translate(speed->XComponent() * 200.0f * gameTime, -speed->YComponent() * 200.0f * gameTime);
        NewDirection(Random(speed->Angle() - 30, speed->Angle() + 30));
        ChooseAnimation();
    }
    else if (obj->Type() == MISSILE)
    {
        GeoWars::zombieKillCount++; // Adicionado: incrementa o contador
        GeoWars::scene->Delete(this, MOVING);
    }
}

void SmallZombie::OnAgroCollision(Object* obj) {

    if (obj->Type() == PLAYER) {
        chase = true;
    }
}

void SmallZombie::NewDirection()
{
    // nova direção aleatória
    speed->RotateTo(angle.Rand());

    // tempo aleatório
    delay = secs.Rand();

    // inicia medição do tempo
    timer->Start();
}

void SmallZombie::NewDirection(Random<float> randomAngle)
{
    // nova direção aleatória
    speed->RotateTo(randomAngle.Rand());

    // tempo aleatório
    delay = secs.Rand();

    // inicia medição do tempo
    timer->Start();
}


void SmallZombie::Update() {
    
    if (life <= 0)
    {
        // Toca o som de explosão
        GeoWars::audio->Play(EXPLODE);

        // Remove o inimigo da cena
        GeoWars::scene->Delete(this, MOVING);

        // Impede que o resto da lógica de Update seja executado para um objeto já marcado para deleção
        return;
    }

    if (chase) {
        // ajusta ângulo do vetor 
        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        baseSpeed = 85.0f;
    }
    else {
        if (timer->Elapsed(delay)) NewDirection();
        baseSpeed = 65.0f;
    }
    
    // tem que fazer código para não permitir sair do mapa, pode ser feito em collision
    

    Translate(speed->XComponent() * baseSpeed * gameTime, -speed->YComponent() * baseSpeed * gameTime);
    if (x < 10 || x < 10 || x > game->Width() - 10 || y > game->Height() - 10) NewDirection();
    ChooseAnimation();
    chase = false;
    anim->NextFrame();
}

void SmallZombie::ChooseAnimation() {
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

void SmallZombie::Draw() {
    anim->Draw(x, y);
}