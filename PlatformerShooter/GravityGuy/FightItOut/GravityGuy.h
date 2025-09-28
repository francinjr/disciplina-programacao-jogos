/**********************************************************************************
// GravityGuy (Arquivo de Cabeçalho)
// 
// Criação:     05 Out 2011
// Atualização: 04 Set 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Jogo estilo plataforma usando a engine do curso
//
**********************************************************************************/

#ifndef _GRAVITYGUY_H_
#define _GRAVITYGUY_H_

// ---------------------------------------------------------------------------------

#include "Game.h"
#include "Audio.h"
#include "Player.h"
#include "Resources.h"
#include "Scene.h"

// ------------------------------------------------------------------------------

enum Sounds {LEVEL1, LEVEL2, MAINMENU, SMALLGUN, RIFLE_SOUND, SHOTGUN};
enum objTypes {PLATFORM, GUN, PLAYER, BULLET, GUNBOX, BUFF};
// ------------------------------------------------------------------------------

class GravityGuy : public Game
{
private:
    static Game * level;            // nível atual do jogo

public:
    static Player * player1;         // jogador 
    static Player* player2;
    static Audio * audio;           // sistema de áudio
    static bool viewBBox;           // estado da bounding box
    static Image* bulletImg;
    const static int GRAVITY = 9 ;
    static Scene* actualScene;
    static int player1Score;
    static int player2Score;
    static int gameWinner;
    static void ResetGame();

    void Init();                    // inicializa jogo
    void Update();                  // atualiza lógica do jogo
    void Draw();                    // desenha jogo
    void Finalize();                // finaliza jogo

    template<class T>
    static void NextLevel()         // muda para próximo nível do jogo
    {
        if (level)
        {
            level->Finalize();
            delete level;
            level = new T();
            level->Init();
        }
    };
};

// ---------------------------------------------------------------------------------

#endif