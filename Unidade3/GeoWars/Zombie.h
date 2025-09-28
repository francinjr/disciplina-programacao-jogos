/**********************************************************************************
// Blue (Arquivo de Cabeçalho)
//
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto faz uma perseguição suavizada
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
    void OnAgroCollision(Object* obj) override;      // resolução da colisão
    void OnCollision(Object* obj) override;      // resolução da colisão
    void Update() override;                      // atualização
    void Draw() override;                        // desenho
    void NewDirection();
    void NewDirection(Random<float> randomAngle);
    void ChooseAnimation();
};


#endif