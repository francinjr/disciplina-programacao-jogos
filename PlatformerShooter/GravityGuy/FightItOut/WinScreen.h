#ifndef _PROGJOGOS_WINSCREEN_H_
#define _PROGJOGOS_WINSCREEN_H_

#include "Game.h"
#include "Sprite.h"
#include "Timer.h"

class WinScreen : public Game
{
private:
    Sprite* winImage = nullptr;
    Timer* timer = nullptr;

public:
    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif