// GameOver.h
#ifndef _MIDNIGHTRUNNER_GAMEOVER_H_
#define _MIDNIGHTRUNNER_GAMEOVER_H_

#include "Game.h"
#include "Sprite.h"

class GameOver : public Game
{
private:
    Sprite* backg = nullptr;

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif