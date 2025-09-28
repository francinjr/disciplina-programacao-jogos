#ifndef _MIDNIGHTRUNNER_ENDPHASESCORE_H_
#define _MIDNIGHTRUNNER_ENDPHASESCORE_H_

#include "Game.h"
#include "Sprite.h"

class EndPhaseScore : public Game
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