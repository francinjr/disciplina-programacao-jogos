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

#ifndef _GEOWARS_SMALLZOMBIE_H_
#define _GEOWARS_SMALLZOMBIE_H_

// ---------------------------------------------------------------------------------

#include "Enemy.h"


// ---------------------------------------------------------------------------------

class SmallZombie : public Enemy
{
private:
    Timer* timer = nullptr;
    float delay;
    Random<float> angle;             
    Random<float> secs;        
public:
    SmallZombie(Player* player, int life, Vector* speed);
    ~SmallZombie();

    void OnCollision(Object* obj) override;      // resolução da colisão
    void OnAgroCollision(Object* obj) override;      // resolução da colisão
    void Update() override;                      // atualização
    void Draw() override;                        // desenho
    void NewDirection();
    void NewDirection(Random<float> randomAngle);
    void ChooseAnimation();
};


#endif