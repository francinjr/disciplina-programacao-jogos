/**********************************************************************************
// Fireworks (Arquivo de Cabe�alho)
//
// Cria��o:     17 Mar 2013
// Atualiza��o: 27 Out 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Efeito de explos�o usando sistema de part�culas
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
    Particles* starGen;            // sistema de part�culas
    random_device rd;               // gerador de n�mero aleat�rio
    mt19937 mt{ rd() };             // gerador mersenne twister
    Rnd RandAngle{ 0.0f, 359.0f };  // �ngulo aleat�rio
    Rnd RandColor{ 0.0f, 1.0f };    // cor aleat�ria

public:
    Debris();
    Debris(float posX, float posY);
    // construtor
    ~Debris();                   // destrutor

    int  Size();                    // quantidade de part�culas
    void Update();                  // atualiza��o
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