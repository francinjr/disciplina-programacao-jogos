
#ifndef _MIDNIGHTRUNNER_LEVEL1_H_
#define _MIDNIGHTRUNNER_LEVEL1_H_


#include "Game.h"
#include "Sprite.h"
#include "Scene.h"
#include "EnemySpawner.h"
#include "Player.h"


class Level1 : public Game
{
private:
    Image  * roadTex    = nullptr;
	// Image * uiHealth   = nullptr;   // imagem de vida do jogador
	Sprite * uiControls = nullptr;   // imagem de controles na tela

    bool viewBBox   = false;          // habilita visualização da bounding box
    EnemySpawner * enemySpawner = nullptr;
    Player* player = nullptr;
     
public:
    static Scene* scene;        // gerenciador de cena
    int totalDistance;    // total de estradas que serão criadas
    static bool requestSceneChange;
    static bool requestVictory;
    static int finalPlayerHealth;

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();
};

#endif