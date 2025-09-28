#ifndef _GEOWARS_H_
#define _GEOWARS_H_

#include "Game.h"
#include "Audio.h"
#include "Scene.h"
#include "Background.h"
#include "Player.h"
#include "Hud.h"

enum ObjectIds { PLAYER, MISSILE, ENEMY, WALLHIT, BOX, DROP, MAPWALL };
enum SoundIds { THEME, START, FIRE, EXPLODE, HITWALL, PLAYER_HIT, THEME_LOOP, MISSION_COMPLETE };

class GeoWars : public Game
{
private:
    Background* backg = nullptr;
    Hud* hud = nullptr;
    bool viewBBox = false;

public:
    static Player* player;
    static Audio* audio;
    static Scene* scene;
    static bool viewHUD;
    static int zombieKillCount;
    static float gameTimeRemaining; // Adicionado: tempo restante de jogo
    static bool isGameOver;

    void Init();
    void Update();
    void Draw();
    void Finalize();
};

#endif