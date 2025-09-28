
#ifndef _MIDNIGHTRUNNER_HOME_H_
#define _MIDNIGHTRUNNER_HOME_H_


#include "Game.h"
#include "Sprite.h"


class Home : public Game
{
private:
    Sprite* backg = nullptr;       // pano de fundo

public:
    void Init();                    // inicialização
    void Update();                  // atualização
    void Draw();                    // desenho
    void Finalize();                // finalização
};

#endif