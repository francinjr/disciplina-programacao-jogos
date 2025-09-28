
#include "MidnightRunner.h"
#include "Level1.h"
#include "Player.h"
#include "Road.h"
#include "Enemy.h"

int Road::distanceCounter = 0; // Contador de distância percorrida
int Road::totalDistance = 0; // Distância total a ser percorrida
bool Road::levelStart = true; 

Road::Road(Image* roadImg, Scene* scene, int distance) 
          : roadImg(roadImg), sceneManager(scene)
{
	totalDistance = distance; 

    hasCreatedNext = false; 

    // Construção da colisão
    Mixed* mixed = new Mixed();

    Rect* wall = nullptr;
    wall = new Rect(250, -360, 280, 359);
    mixed->Insert(wall);

    wall = new Rect(-282, -360, -252, 359);
    mixed->Insert(wall);

    BBox(mixed);
    // --------------------

    road = new Sprite(roadImg);
    MoveTo(window->CenterX(), window->CenterY());

    type = ROAD;
}



Road::~Road() 
{
    delete road;
	levelStart = true; 
}

void Road::OnCollision(Object* obj) 
{ 

}


void Road::Update()
{
    if (!levelStart && !isEnding())
    {
        // Controles de velocidade (usando a velocidade GLOBAL)
        if (window->KeyDown('A'))
        {
            globalVel += ACCELERATION * gameTime; // Acelera globalmente

            // Aplica limite máximo de 1500
            if (globalVel > 1800.0f)
            {
                globalVel = 1800.0f;
            }
        }

        else if (window->KeyDown('Z'))
        {
            globalVel -= BRAKE_POWER * gameTime;  // Desacelera globalmente
            if (globalVel < 0) globalVel = 0;
        }
        else
        {
            // Volta suavemente para a velocidade padrão
            if (globalVel > DEFAULT_SPEED)
            {
                globalVel -= FRICTION * gameTime;
                if (globalVel < DEFAULT_SPEED) globalVel = DEFAULT_SPEED;
            }
            else if (globalVel < DEFAULT_SPEED)
            {
                globalVel += FRICTION * gameTime;
                if (globalVel > DEFAULT_SPEED) globalVel = DEFAULT_SPEED;
            }
        }

        // ★★ Move a estrada usando a velocidade GLOBAL ★★
        Translate(0, globalVel * gameTime);

        // Cria novo segmento de estrada quando necessário
        if (Y() > 0 && !hasCreatedNext) {
            hasCreatedNext = true;
            distanceCounter += 1;

            Road* nextRoad = new Road(roadImg, sceneManager);
            nextRoad->MoveTo(window->CenterX(), Y() - window->Height());

            sceneManager->Add(nextRoad, STATIC);
        }

        // Remove segmentos que saíram da tela
        if (Y() > 1.5f * window->Height())
        {
            sceneManager->Delete();
        }

    }
}

