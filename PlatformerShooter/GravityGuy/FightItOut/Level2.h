/**********************************************************************************
// Level2 (Arquivo de Cabe�alho)
//
// Descri��o:   N�vel 2 do jogo
//
**********************************************************************************/

#ifndef _GRAVITYGUY_LEVEL2_H_
#define _GRAVITYGUY_LEVEL2_H_

#include "Game.h"
#include "Scene.h"
#include "Player.h"
#include "Spawner.h"
#include "Font.h"
#include "Timer.h"

class Level2 : public Game
{
private:
    Sprite* backg = nullptr;
    Spawner* spawner = nullptr;
    Sprite* platform = nullptr;
    Sprite* round2Image = nullptr;

    // Itens para a mensagem "Round 2"
    Font* font = nullptr;
    Timer* timer = nullptr;
    bool   showingMessage = true;
    float  messageTime = 3.0f; // 3 segundos
    Sprite* p1winsImage = nullptr;
    Sprite* p2winsImage = nullptr;


public:
    static Scene* scene;
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif