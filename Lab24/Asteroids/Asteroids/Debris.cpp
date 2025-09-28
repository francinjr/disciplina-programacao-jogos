/**********************************************************************************
// Debris (Código Fonte)
//
// Criação:     07 Fev 2013
// Atualização: 25 Out 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Animação de explosão
//
**********************************************************************************/

#include "Debris.h"
#include "Asteroids.h"
#include "Particles.h"
#include "Object.h"

// ---------------------------------------------------------------------------------

Debris::Debris(float posX, float posY)
{
    Generator starmaker;
    starmaker.imgFile = "Resources/Particle.png";   // arquivo de imagem
    //starmaker.angle = RandAngle(mt);            // dire��o das estrelas
    starmaker.spread = 360.0f;                  // espalhamento em graus
    starmaker.lifetime = 2.0f;                  // tempo de vida (em segundos)
    starmaker.frequency = 0.000f;               // tempo entre gera��o de novas part�culas
    starmaker.percentToDim = 0.6f;              // desaparece ap�s 60% da vida
    starmaker.minSpeed = 105.0f;                 // velocidade m�nima das part�culas
    starmaker.maxSpeed = 250.0f;                // velocidade m�xima das part�culas
    starmaker.color.r = 0.5f;          // cor aleat�ria para part�cula
    starmaker.color.g = 0.5f;          // cor aleat�ria para part�cula
    starmaker.color.b = 0.5f;          // cor aleat�ria para part�cula
    starmaker.color.a = 1.0f;

    // cria sistema de part�culas
    starGen = new Particles(starmaker);

    // gera 50 part�culas na posi��o do mouse
    starGen->Generate(posX, posY, 15);
    type = ROCK;
}

// ---------------------------------------------------------------------------------

Debris::~Debris()
{
    delete starGen;
}

// ---------------------------------------------------------------------------------

void Debris::Update()
{
    // atualiza posição de cada partícula
    starGen->Update(gameTime);

    // remove da cena quando todas as partículas estão inativas
    if (starGen->Inactive())
        Asteroids::scene->Delete();
}

// ---------------------------------------------------------------------------------