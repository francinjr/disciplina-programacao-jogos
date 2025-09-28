/**********************************************************************************
// Wave (Arquivo de Cabeçalho)
//
// Criação:     06 Ago 2019
// Atualização: 05 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Cria uma onda de inimigos
//
**********************************************************************************/

#ifndef _WAVESDEMO_WAVE_H_
#define _WAVESDEMO_WAVE_H_

// --------------------------------------------------------------------------------

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Random.h"

// --------------------------------------------------------------------------------

class Wave : public Object
{
private:
    int numX, numY;             // número de inimigos que cabem na tela
    float posX, posY;           // posição dos inimigos 
    Random<int> position;       // valor aleatório para posição
    Random<float> delay;        // valor aleatório para tempo
    Timer timer;                // medidor de tempo
    float waveDelay;            // atraso para a próxima onda
    bool newWave;               // enviar nova onda

public:
    Wave();                     // construtor
    ~Wave();                    // destrutor

    void Update();              // atualização
    void Draw();                // desenho
};

// ------------------------------------------------------------------------------

#endif
