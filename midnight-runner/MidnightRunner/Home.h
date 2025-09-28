
#ifndef _MIDNIGHTRUNNER_HOME_H_
#define _MIDNIGHTRUNNER_HOME_H_


#include "Game.h"
#include "Sprite.h"


class Home : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo

public:
    void Init();                    // inicializa��o
    void Update();                  // atualiza��o
    void Draw();                    // desenho
    void Finalize();                // finaliza��o
};

#endif