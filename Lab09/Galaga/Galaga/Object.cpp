/**********************************************************************************
// Object (C�digo Fonte)
//
// Cria��o:     01 Out 2007
// Atualiza��o: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descri��o:   Essa � a classe base para todos objetos do jogo.
//
//              Um objeto do jogo � qualquer coisa que poss�mos querer desenhar
//              ou interagir dentro do jogo. Por exemplo, um soldado, um pr�dio,
//              um proj�til, uma forma geom�trica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicializa��o de vari�veis est�ticas da classe

Window* & Object::window   = Engine::window;           // ponteiro para a janela
Game*   & Object::game     = Engine::game;             // ponteiro para o jogo
float   & Object::gameTime = Engine::frameTime;        // tempo do �ltimo quadro

// -------------------------------------------------------------------------------

Object::Object() : posX(0.0f), posY(0.0f), posZ(0.5f)
{
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------