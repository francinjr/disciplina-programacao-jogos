/**********************************************************************************
// Object (Código Fonte)
//
// Criação:     01 Out 2007
// Atualização: 26 Fev 2023
// Compilador:  Visual C++ 2022
//
// Descrição:   Essa é a classe base para todos objetos do jogo.
//
//              Um objeto do jogo é qualquer coisa que possámos querer desenhar
//              ou interagir dentro do jogo. Por exemplo, um soldado, um prédio,
//              um projétil, uma forma geométrica, etc.
//
**********************************************************************************/

#include "Object.h"
#include "Engine.h"

// -------------------------------------------------------------------------------
// Inicialização de variáveis estáticas da classe

Window* & Object::window   = Engine::window;           // ponteiro para a janela
Game*   & Object::game     = Engine::game;             // ponteiro para o jogo
float   & Object::gameTime = Engine::frameTime;        // tempo do último quadro

// -------------------------------------------------------------------------------

Object::Object() : posX(0.0f), posY(0.0f), posZ(0.5f)
{
}

// -------------------------------------------------------------------------------

Object::~Object()
{
}

// -------------------------------------------------------------------------------