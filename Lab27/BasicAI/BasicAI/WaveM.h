/**********************************************************************************
// WaveM (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 11 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Cria uma onda de inimigos Magenta
//
**********************************************************************************/

#ifndef _BASICAI_WAVEM_H_
#define _BASICAI_WAVEM_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class WaveM : public Object
{
private:
    float pX, pY;       // posição dos inimigos 
    Random<float> posX; // valor aleatório para posição X
    Random<float> posY; // valor aleatório para posição Y
    Random<float> secs; // valor aleatório de segundos
    Timer timer;        // medidor de tempo
    float delay;        // atraso para a próxima onda

public:
    WaveM();            // construtor
    ~WaveM();           // destrutor

    void Update();      // atualização
    void Draw();        // desenho
};

// ------------------------------------------------------------------------------

#endif
