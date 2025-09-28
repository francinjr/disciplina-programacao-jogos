/**********************************************************************************
// Wave (Arquivo de Cabe�alho)
//
// Cria��o:     06 Ago 2019
// Atualiza��o: 05 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Cria uma onda de inimigos
//
**********************************************************************************/

#ifndef _CHASEDEMO_WAVE_H_
#define _CHASEDEMO_WAVE_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class Wave : public Object
{
private:
    float pX, pY;               // posi��o dos inimigos 
    Random<float> posX;         // valor aleat�rio para posi��o X
    Random<float> posY;         // valor aleat�rio para posi��o Y
    Random<float> secs;         // valor aleat�rio de segundos
    Timer timer;                // medidor de tempo
    float delay;                // atraso para a pr�xima onda

public:
    Wave();                     // construtor
    ~Wave();                    // destrutor

    void Update();              // atualiza��o
    void Draw();                // desenho
};

// ------------------------------------------------------------------------------

#endif
