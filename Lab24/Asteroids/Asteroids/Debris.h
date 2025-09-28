/**********************************************************************************
// Fireworks (Arquivo de Cabeçalho)
//
// Criação:     17 Mar 2013
// Atualização: 27 Out 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Efeito de explosão usando sistema de partículas
//
**********************************************************************************/

#ifndef _REFINERY_FIREWORKS_H_
#define _REFINERY_FIREWORKS_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Particles.h"

#include <random>
using std::random_device;
using std::mt19937;
using Rnd = std::uniform_real_distribution<float>;

// ---------------------------------------------------------------------------------

class Debris : public Object
{
private:
    Particles* starGen;            // sistema de partículas
    random_device rd;               // gerador de número aleatório
    mt19937 mt{ rd() };             // gerador mersenne twister
    Rnd RandAngle{ 0.0f, 359.0f };  // ângulo aleatório
    Rnd RandColor{ 0.0f, 1.0f };    // cor aleatória

public:
    Debris();
    Debris(float posX, float posY);
    // construtor
    ~Debris();                   // destrutor

    int  Size();                    // quantidade de partículas
    void Update();                  // atualização
    void Draw();                    // desenho
};

// ---------------------------------------------------------------------------------

inline int Debris::Size()
{
    return starGen->Size();
}

inline void Debris::Draw()
{
    starGen->Draw(Layer::MIDDLE, 0.0f);
}

// ---------------------------------------------------------------------------------


#endif