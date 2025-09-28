/**********************************************************************************
// Player (Código Fonte)
// 
// Criação:     20 Abr 2012
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Define uma classe para o jogador 
//
**********************************************************************************/

#include "Player.h"
#include "GravityGuy.h"
#include "Platform.h"
#include "GunBox.h"
#include "Bullet.h" 
#include "SpawnRegistry.h"
// ---------------------------------------------------------------------------------

Player::Player(PlayerNumber pn)
{
    playerNumber = pn;
    damage = 0;
    if(pn == 0) tileset = new TileSet("Resources/sprite_azul.png", 32, 52, 1, 2);
    else tileset = new TileSet("Resources/sprite_vermelho.png", 32, 52, 1, 2);
    anim = new Animation(tileset, 0.620f, true);

    // sequências de animação do player
    uint left[1] = {1};
    uint right[1] = {0};
    uint idle[1] = { 0 };
    anim->Add(LEFT, left, 1);
    anim->Add(RIGHT, right, 1);
    anim->Add(IDLE, idle, 1);
    // cria bounding box
    BBox(new Rect(
        -1.0f * tileset->TileWidth() / 2.0f,
        -1.0f * tileset->TileHeight() / 2.0f,
        tileset->TileWidth() / 2.0f,
        tileset->TileHeight() / 2.0f));
    
    type = PLAYER;

    speedX = 0;
    speedY = GravityGuy::GRAVITY;
    
    state = RIGHT;

    // posição inicial
    if(playerNumber == FIRST){ // spawna em x canto 
    }

    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    anim->Select(IDLE);
 
    gun = new Gun(state == RIGHT ? Right() : Left(), Y() + 7, PISTOL, playerNumber);
    
}

// ---------------------------------------------------------------------------------

Player::~Player()
{
    delete anim;
    delete tileset;    
    delete gun;
    delete ignoreObj;
}

// ---------------------------------------------------------------------------------

void Player::Reset()
{
    // volta ao estado inicial
    MoveTo(window->CenterX(), 24.0f, Layer::FRONT);
    gun = gun = new Gun(state == RIGHT ? Right() : Left(), Y() + 7, PISTOL, playerNumber);
    playerBuffs.clear();
    consecutiveJumps = 1;
    speedY = 0;
    damage = 0;
    ignoreObj = nullptr;
}


// ---------------------------------------------------------------------------------

PlayerNumber Player::getPlayerNumber()
{
    return playerNumber;
}

void Player::OnCollision(Object * obj)
{
    if(obj->Type() == PLATFORM){
        // mantém personagem em cima da plataforma
            Platform* plat = (Platform*)obj;
            if (ignoreObj) {
                if (ignoreObj != plat) {
                    MoveTo(x, plat->Top() - (tileset->TileHeight() / 2.0f));
                    speedY = 0;
                    consecutiveJumps = 0;
                    ignoreObj = nullptr;
                }

            }
            else {
                if (Y() <= plat->Top() + 5 && Bottom() <= plat->Y() +3) {
                    // tá em cima

                    MoveTo(x, plat->Top() - (tileset->TileHeight() / 2.0f));
                    speedY = 0;
                    consecutiveJumps = 0;
                    // se estiver em cima da plataforma e apertar pra descer
                    if (playerNumber == FIRST) {
                        if (window->KeyPress(VK_DOWN)) {
                            ignoreObj = obj;
                            speedY = 0;
                        }
                    }
                    else {
                        if (window->KeyPress('S')) {
                            ignoreObj = obj;
                            speedY = 0;
                        }
                    }
                }
            }
            
    }

    if (obj->Type() == BULLET) {
        Bullet* bullet = (Bullet*)obj;
        int damage = bullet->getDamage();
        // o lado que ela da o knoback, depende de onde ela está vindo
        int buffDamage = 0;
        for (auto const& par : playerBuffs) {
            if (par.first == EXTRA_DAMAGE) buffDamage += 20;
        }
        this->damage += damage + buffDamage;
        if (this->damage >= MAX_DAMAGE) this->damage = MAX_DAMAGE;
        int knockback = this->damage;
        if (std::abs(knockback) > MAX_DAMAGE) knockback = MAX_DAMAGE;
        this->knockback = knockback;
        this->knockbackSignal = bullet->getVel() > 0 ? 1 : -1;
        GravityGuy::actualScene->Delete(obj, BULLET);
        // tem que dar: dano, knockback e a bala deve desaparecer
    }

    if (obj->Type() == GUNBOX) {
        GunBox* box = (GunBox*)obj;
        GravityGuy::actualScene->Delete(gun, STATIC);
        gun = new Gun(state == RIGHT ? Right() : Left(), Y() + 7, box->GetGunType(), playerNumber);
        for (auto const& par : playerBuffs) {
            if (par.first == RAPID_FIRE) gun->setExtraFireRating(0.01f);
        }
        // talvez adicionar alguma animação da caixa sendo aberta ou se destroçando
        SpawnRegistry::unregisterBox(box);
        GravityGuy::actualScene->Delete(box, MOVING);
        GravityGuy::actualScene->Add(gun, STATIC);
    }
    if (obj->Type() == BUFF) {
        Buff* buff = (Buff*)obj;

        if (buff->GetBuffType() == HEAL) {
            this->damage = this->damage / 2.0f;
        }
        else if (buff->GetBuffType() == SHIELD) {
           //;
        }
        else {
            playerBuffs[buff->GetBuffType()] += 1;
        }


        SpawnRegistry::unregisterBuff(buff);
        GravityGuy::actualScene->Delete(buff, MOVING);
    }
    
}

// ---------------------------------------------------------------------------------

void Player::Update()
{
    if (playerNumber == FIRST) {

        if (window->KeyDown(VK_RIGHT)) {
            speedX = 100;
            state = RIGHT;
            gun->changeSide(1); // 1 para right
        }
        else if (window->KeyDown(VK_LEFT)) {
            speedX = -100;
            state = LEFT;
            gun->changeSide(0); // 0 para left
        }
        else {
            speedX = 0;
        }
        if (window->KeyPress(VK_UP)) {
            if (consecutiveJumps < 2) {
                MoveTo(X(), Y() - 1);
                speedY = -30 * GravityGuy::GRAVITY; // jump force
                consecutiveJumps++;
            }
            // tem que implementar o double jump
        }
        


        if (window->KeyPress(VK_LBUTTON)) {
            // atira
            if (gun) {
                Bullet* bullet = gun->Shoot();
                if (bullet) {
                    float posX = state == RIGHT ? x + tileset->TileWidth() : x - tileset->TileWidth();
                    bullet->MoveTo(posX, y, Layer::UPPER);
                    gun->setState(state == RIGHT ? SHOOT_RIGHT : SHOOT_LEFT);
                    GravityGuy::actualScene->Add(bullet, MOVING);


                    GravityGuy::audio->Volume(SMALLGUN, 0.20f);
                    GravityGuy::audio->Play(SMALLGUN);
                }
            }
        }
        else {
            gun->setState(state == RIGHT ? AIM_RIGHT : AIM_LEFT);
        }

   }
    else {
        if (window->KeyDown('D')) {
            speedX = 100;
            state = RIGHT;
            gun->changeSide(1); // 1 para right
        }
        else if (window->KeyDown('A')) {
            speedX = -100;
            state = LEFT;
            gun->changeSide(0); // 0 para left
        }
        else {
            speedX = 0;
        }
        if (window->KeyPress('W')) {
            if (consecutiveJumps < 2) {
                MoveTo(X(), Y() - 1);
                speedY = -30 * GravityGuy::GRAVITY; // jump force
                consecutiveJumps++;
                
            }
            // tem que implementar o double jump
        }
        


        if (window->KeyPress(VK_SPACE)) {
            // atira
            if (gun) {
                Bullet* bullet = gun->Shoot();
                if (bullet) {
                    float posX = state == RIGHT ? x + tileset->TileWidth() : x - tileset->TileWidth();
                    bullet->MoveTo(posX, y, Layer::UPPER);
                    GravityGuy::actualScene->Add(bullet, MOVING);

                    gun->setState(state == RIGHT ? SHOOT_RIGHT : SHOOT_LEFT);
                    GravityGuy::audio->Volume(SMALLGUN, 0.20f);
                    GravityGuy::audio->Play(SMALLGUN);

                }
            }    
        }
        else {
            gun->setState(state == RIGHT ? AIM_RIGHT : AIM_LEFT);
        }
    }

   speedY += GravityGuy::GRAVITY;
   
   if (knockback < 0 || knockback == 0) knockback = 0;
   else knockback += -15;
   

   if (speedY > 200) speedY = 200;

   if(knockbackSignal != 0)
       Translate(((knockback * knockbackSignal)+speedX) * gameTime, speedY * gameTime);
   else Translate(speedX * gameTime, speedY * gameTime);

   anim->Select(state);
   anim->NextFrame();
}

// ---------------------------------------------------------------------------------