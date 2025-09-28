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

#ifndef _GEOWARS_BIGZOMBIE_H_
#define _GEOWARS_BIGZOMBIE_H_

// ---------------------------------------------------------------------------------

#include "Enemy.h"

// ---------------------------------------------------------------------------------

class BigZombie : public Enemy
{
private:
    Timer* timer = nullptr;
    float delay;
    Random<float> angle;
    Random<float> secs;
public:
    BigZombie(Player* player, int life, Vector* speed);
    ~BigZombie();
    void OnAgroCollision(Object* obj) override;      // resolução da colisão
    void OnCollision(Object* obj) override;      // resolução da colisão
    void Update() override;                      // atualização
    void Draw() override;                        // desenho
    void NewDirection();
    void ChooseAnimation();
    void NewDirection(Random<float> randomAngle);
};


#endif