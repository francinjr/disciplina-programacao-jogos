/**********************************************************************************
// Blue (Arquivo de Cabe�alho)
//
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Objeto faz uma persegui��o suavizada
//
**********************************************************************************/

#ifndef _GEOWARS_ZOMBIE_H_
#define _GEOWARS_ZOMBIE_H_

// ---------------------------------------------------------------------------------

#include "Enemy.h"


// ---------------------------------------------------------------------------------

class Zombie : public Enemy
{
private:
    Timer* timer = nullptr;
    float delay;
    Random<float> angle;
    Random<float> secs;
public:
    Zombie(Player* player, int life, Vector* speed);
    ~Zombie();
    void OnAgroCollision(Object* obj) override;      // resolu��o da colis�o
    void OnCollision(Object* obj) override;      // resolu��o da colis�o
    void Update() override;                      // atualiza��o
    void Draw() override;                        // desenho
    void NewDirection();
    void NewDirection(Random<float> randomAngle);
    void ChooseAnimation();
};


#endif