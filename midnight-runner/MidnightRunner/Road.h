#ifndef _MIDNIGHTRUNNER_ROAD_H_
#define _MIDNIGHTRUNNER_ROAD_H_

#include "Object.h"
#include "Sprite.h"
#include "Scene.h"

class Road : public Object {
private:
    Sprite* road;
    Image* roadImg;
    Scene* sceneManager;
    bool hasCreatedNext;

public:
    // Constantes de física
    inline static const float DEFAULT_SPEED = 600.0f;   // Velocidade padrão (cruzeiro)
    inline static const float ACCELERATION  = 50.0f;   // Aceleração ao pressionar W
    inline static const float BRAKE_POWER   = 600.0f;   // Desaceleração ao pressionar S
    inline static const float FRICTION      = 50.0f;   // Atrito para voltar à velocidade padrão

    // Variável estática compartilhada por TODAS as estradas
    inline static float globalVel = DEFAULT_SPEED;

    static bool levelStart;
	static int totalDistance; 
	static int distanceCounter; 

    Road(Image* roadImg, Scene* scene, int distance = totalDistance);
    ~Road();

    void OnCollision(Object* obj);
    void Update();
    void Draw();

    static bool isEnding() { return (Road::distanceCounter > Road::totalDistance); }
};

inline void Road::Draw()
{
    road->Draw(x, y, Layer::BACK);
}


#endif