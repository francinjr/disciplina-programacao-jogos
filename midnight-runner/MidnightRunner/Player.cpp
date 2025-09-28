#include <cmath>
#include "MidnightRunner.h"
#include "Player.h"
#include "Road.h"
#include "Home.h"
#include "Engine.h"
#include "Level1.h"


Player::Player()
{
	Rect* rect = new Rect(-35, -90, 35, 90);
    


	/*Circle* circle = new Circle(43);
    circle->MoveTo(0, -58);
	mixed->Insert(circle);

	circle = new Circle(43);
	circle->MoveTo(0, 61);
	mixed->Insert(circle);*/

    BBox(rect);


    player = new Sprite("Resources/Player.png");
    lifeImage = new Sprite("Resources/UI_Health_4.png");

    iniPos = window->CenterY() + 220;

    MoveTo(window->CenterX(), iniPos + 300);

    type = PLAYER;

    lifeCount = 4;
}

Player::~Player() 
{
    delete player;
    delete lifeImage;

    Road::globalVel = Road::DEFAULT_SPEED;
    Road::distanceCounter = 0;
}

void Player::OnCollision(Object* obj)
{
    // Lógica de colisão
    if (obj->Type() == ROAD) 
    {
        Road* road = (Road*)obj;
        if (road->globalVel < 100) road->globalVel = 100.0f;
        else if (road->globalVel > 0) road->globalVel -= 30.0f;


        float lateralSpeedFactor = Road::globalVel / Road::DEFAULT_SPEED;


        if (X() > window->CenterX())
            MoveTo(730 - (player->Width() - 16.0f) / 2, Y());

        if (X() < window->CenterX())
            MoveTo(226 + (player->Width() - 16.0f) / 2, Y());
    }

    if (obj->Type() == TRAFFIC) {
        lifeCount--;
        Road::globalVel = 50;
        
        if (lifeCount == 3) {
            lifeImage = new Sprite("Resources/UI_Health_3.png");
        }
        else if (lifeCount == 2) {
            lifeImage = new Sprite("Resources/UI_Health_2.png");
        }
        else if (lifeCount == 1) {
            lifeImage = new Sprite("Resources/UI_Health_1.png");
        }
        else {
            Level1::requestSceneChange = true;
        }

        enum CollisionSide {
            LEFT,
            RIGHT,
            TOP,
            BOTTOM,
        };
        Rect* staticRect = dynamic_cast<Rect*>(obj->BBox());

        Rect* movingRect = dynamic_cast<Rect*>(BBox());
        float distLeft = (obj->X() + staticRect->right) - (X() + movingRect->left);
        float distRight = (X() + movingRect->right) - (obj->X() + staticRect->left);
        float distTop = (obj->Y() + staticRect->bottom) - (Y() + movingRect->top);
        float distBottom = (Y() + movingRect->bottom) - (obj->Y() + staticRect->top);

        float minDist = std::abs(distLeft);
        CollisionSide side = LEFT;

        side = (std::abs(distRight) < minDist) ? RIGHT : side;
        minDist = (std::abs(distRight) < minDist) ? std::abs(distRight) : minDist;

        side = (std::abs(distTop) < minDist) ? TOP : side;
        minDist = (std::abs(distTop) < minDist) ? std::abs(distTop) : minDist;

        side = (std::abs(distBottom) < minDist) ? BOTTOM : side;
        minDist = (std::abs(distBottom) < minDist) ? std::abs(distBottom) : minDist;

        switch (side) {
        case LEFT:
            MoveTo((obj->X() + staticRect->right) + player->Width() / 2.0f, y);
            break;
        case RIGHT:
            MoveTo((obj->X() + staticRect->left) - player->Width() / 2.0f, y);
            break;
        case TOP:
            MoveTo(x, (obj->Y() + staticRect->bottom) + player->Height()/ 2.0f);
            break;
        case BOTTOM:
            MoveTo(x, (obj->Y() + staticRect->top) - player->Height() / 2.0f);
            break;
        }
    }
}

void Player::Update()
{
    // ★ Calcula a velocidade lateral baseada na velocidade da estrada ★
    float lateralSpeedFactor = Road::globalVel / Road::DEFAULT_SPEED;
    float adjustedLateralSpeed = 300.0f * lateralSpeedFactor;


    // ★ Limita a velocidade lateral mínima para evitar movimento zero ★
    if (adjustedLateralSpeed < 25.0f) adjustedLateralSpeed = 60.0f;


    if (Road::globalVel == 0.0f) adjustedLateralSpeed = 0.0f;


    if (window->KeyDown(VK_LEFT)) {
        Translate(-adjustedLateralSpeed * gameTime, 0);
    }


    if (window->KeyDown(VK_RIGHT)) {
        Translate(adjustedLateralSpeed * gameTime, 0);
    }


    if (Road::levelStart || Road::isEnding()) {

        if (Y() > iniPos || Road::isEnding())
        {
            Translate(0, -Road::globalVel * gameTime);
        } 
        else 
        {
            Road::levelStart = false;
			MoveTo(X(), iniPos);
        }
	}

    if (Y() < 0 - player->Height() && Road::isEnding())
    {
        Level1::requestVictory = true;
    }
}


void Player::Draw()
{
    player->Draw(x, y, Layer::LOWER);
    lifeImage->Draw(window->Width() - 34 - (lifeImage->Width() / 2.0f), 
                    window->Height() - 34 - (lifeImage->Height() / 2.0f), 
                    Layer::FRONT);
}
