/**********************************************************************************
// Galaga (Arquivo de Cabe�alho)
//
// Cria��o:     23 Set 2011
// Atualiza��o: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Usa a classe Scene para gerenciar muitos objetos na tela
//
**********************************************************************************/

#include "Game.h"
#include "Scene.h"
#include "Sprite.h"

// ------------------------------------------------------------------------------

class Galaga : public Game
{
private:
    Sprite * backg = nullptr;
    Sprite * title = nullptr;

public:
    static Scene * scene;

    void Init();
    void Update();
    void Draw();
    void Finalize();
};

// ------------------------------------------------------------------------------
