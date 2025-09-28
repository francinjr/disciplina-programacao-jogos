/**********************************************************************************
// Level2 (Arquivo de Cabe�alho)
//
// Descri��o:   N�vel 2 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL3_H_
#define _GRAVITYGUY_LEVEL3_H_

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Spawner.h"
#include "Font.h"
#include "Timer.h"

class Level3 : public Game
{
private:
    Sprite* backg = nullptr;
    Spawner* spawner = nullptr;
    
    Sprite* plataforma = nullptr;
    Sprite* round3Image = nullptr;

    Font* font = nullptr;
    Timer* timer = nullptr;
    bool   showingMessage = true;
    float  messageTime = 3.0f;

public:
    static Scene* scene;
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif