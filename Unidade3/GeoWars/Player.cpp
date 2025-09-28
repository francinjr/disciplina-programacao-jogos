/**********************************************************************************
// Player (Código Fonte)
//
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Define a classe jogador
//
**********************************************************************************/

#include "Player.h" 
#include "Missile.h"
#include "GeoWars.h"
#include "Drop.h"
#include "MapWall.h"

// -------------------------------------------------------------------------------

Player::Player()
{
    health = 100;
    damageCooldown = 0.0f; // Inicializa o cooldown

    // configuração do objeto
    tileset = new TileSet("Resources/PlayerTile.png", 68, 68, 7, 28);
    anim = new Animation(tileset, 0.200f, true);

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

    speed = new Vector(0.0f, 0.0f);

    BBox(new Rect(-20, -20, 20, 20));

    MoveTo(game->CenterX() - 20, game->CenterY());
    type = PLAYER;

    // configuração de controle 
    gamepad = new Controller();
    xboxOn = gamepad->XboxInitialize();

    if (!xboxOn)
        controllerOn = gamepad->Initialize();
}

// -------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;
    delete speed;
    delete gamepad;
}

// -------------------------------------------------------------------------------

void Player::OnCollision(Object* obj) {

    if (obj->Type() == MAPWALL) {
        speed->RotateTo(speed->Angle() + 180);
        Translate(speed->XComponent() * gameTime, -speed->YComponent() * gameTime);
        speed->ScaleTo(0);
    }
    // Lógica de dano ao colidir com inimigo
    else if (obj->Type() == ENEMY && damageCooldown <= 0) // Só toma dano se o cooldown acabou
    {
        // Reduz a vida do jogador em 25 pontos (100 / 4 = 25)
        TakeDamage(25);
        damageCooldown = 1.0f;

        // Ativa 1 segundo de invencibilidade
        damageCooldown = 1.0f;
        soundCooldown = 0.0f;
    }
    else if (obj->Type() == DROP) {
        // ... (código para pegar drops) ...
    }
}


void Player::Update()
{
    // Atualiza o cooldown de dano
    if (damageCooldown > 0)
    {
        damageCooldown -= gameTime;
    }

    // Se a vida do jogador chegar a zero, fecha o jogo
    if (health <= 0)
    {
        window->Close();
        return;
    }

    if (soundCooldown > 0)
    {
       soundCooldown -= gameTime;
    }

    // Constantes de movimento para fácil ajuste
    const float ACCELERATION = 800.0f;
    const float MAX_SPEED = 250.0f;
    const float FRICTION = 0.90f;

    bool moved = false;
    Vector direction;

    // --- LÓGICA DE INPUT ---
    if (window->KeyDown(VK_RIGHT)) {
        direction.Add(Vector(0.0f, 1.0f));
        moved = true;
    }
    if (window->KeyDown(VK_LEFT)) {
        direction.Add(Vector(180.0f, 1.0f));
        moved = true;
    }
    if (window->KeyDown(VK_UP)) {
        direction.Add(Vector(90.0f, 1.0f));
        moved = true;
    }
    if (window->KeyDown(VK_DOWN)) {
        direction.Add(Vector(270.0f, 1.0f));
        moved = true;
    }

    // --- LÓGICA DE FÍSICA ---
    if (moved)
    {
        Vector accelerationVec(direction.Angle(), ACCELERATION * gameTime);
        speed->Add(accelerationVec);

        if (speed->Magnitude() > MAX_SPEED)
        {
            speed->ScaleTo(MAX_SPEED);
        }
    }
    else
    {
        speed->Scale(FRICTION);
    }

    // --- LÓGICA DE ANIMAÇÃO ---
    if (speed->Magnitude() < 1.0f)
    {
        if (state == UP || state == IDLE_UP) state = IDLE_UP;
        else if (state == DOWN || state == IDLE_DOWN) state = IDLE_DOWN;
        else if (state == LEFT || state == IDLE_LEFT) state = IDLE_LEFT;
        else if (state == RIGHT || state == IDLE_RIGHT) state = IDLE_RIGHT;
    }
    else
    {
        float currentAngle = speed->Angle();
        if (currentAngle > 45.0f && currentAngle <= 135.0f) state = UP;
        else if (currentAngle > 135.0f && currentAngle <= 225.0f) state = LEFT;
        else if (currentAngle > 225.0f && currentAngle <= 315.0f) state = DOWN;
        else state = RIGHT;
    }
    anim->Select(state);
    anim->NextFrame();

    // --- APLICAÇÃO DO MOVIMENTO E AÇÕES ---
    Translate(speed->XComponent() * gameTime, -speed->YComponent() * gameTime);

    // Dispara míssil
    if (window->KeyPress(VK_SPACE))
    {
        GeoWars::audio->Play(FIRE);
        GeoWars::scene->Add(new Missile(), MOVING);
    }

    // Restringe o jogador à área do jogo
    if (x < 10) MoveTo(10, y);
    if (y < 10) MoveTo(x, 10);
    if (x > game->Width() - 10) MoveTo(x, game->Width() - 10, y);
    if (y > game->Height() - 10) MoveTo(x, game->Height() - 10);
}

// ---------------------------------------------------------------------------------

void Player::Draw()
{
    // Futuramente, podemos fazer o jogador piscar quando estiver invencível
    anim->Draw(x, y, Layer::MIDDLE, 1.0f);
}

void Player::TakeDamage(int damage)
{
    health -= damage;
    GeoWars::audio->Play(PLAYER_HIT);
}

int Player::Health() const
{
    return health;
}

// -------------------------------------------------------------------------------