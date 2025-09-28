/**********************************************************************************
// Object (Arquivo de Cabe�alho)
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

#ifndef _PROGJOGOS_OBJECT_H_
#define _PROGJOGOS_OBJECT_H_

// -----------------------------------------------------------------------------

#include "Types.h"                  // usando os tipos personalizados da engine
#include "Game.h"                   // representa��o de um jogo
#include "Window.h"                 // janela usada para o jogo

// -----------------------------------------------------------------------------

class Object
{
private:
    float posX, posY, posZ;         // coordenadas do objeto 

protected:
    // ------------------
    // membros protegidos
    // ------------------
    // membros s�o privados para o mundo exterior, mas 
    // p�blicos para as classes derivadas de Object

    static Window* & window;        // janela do jogo 
    static Game* & game;            // jogo em execu��o
    static float & gameTime;        // tempo do �ltimo quadro

    // ---------------------
    // membros constantes
    // ---------------------
    // fornecem comodidade no acesso da posi��o do objeto
    // atrav�s dos atributos (x,y,z) mas a altera��o s� 
    // pode ser feita pelos m�todos Translate e MoveTo

    const float& x = posX;          // coordenada x do objeto
    const float& y = posY;          // coordenada y do objeto
    const float& z = posZ;          // coordenada z do objeto

public:
    Object();                       // construtor padr�o
    virtual ~Object();              // destrutor virtual

    // ------------------------
    // fun��es virtuais    
    // ------------------------
    // podem ser sobrescritas na classe derivada
    // e chamadas corretamente mesmo usando um
    // ponteiro para a classe base

    // retorna coordenada x do objeto
    virtual float X() const;

    // retorna coordenada y do objeto
    virtual float Y() const;

    // retorna coordenada z do objeto
    virtual float Z() const;

    // move o objeto por (deltaX, deltaY, deltaZ)
    virtual void Translate(float dx, float dy, float dz = 0.0f);

    // move o objeto para as coordenadas (x,y,z) indicadas
    virtual void MoveTo(float px, float py, float pz);

    // move o objeto para as coordenadas (x,y) indicadas
    virtual void MoveTo(float px, float py);

    // ------------------------
    // fun��es virtuais puras    
    // ------------------------     
    // devem ser obrigatoriamente sobrescritas na classe derivada

    // atualiza estado do objeto
    virtual void Update() = 0;

    // desenha o objeto na tela
    virtual void Draw() = 0;
};

// -----------------------------------------------------------------------------
// M�todos Inline

// retorna coordenada x do objeto
inline float Object::X() const
{  return posX; }

// retorna coordenada y do objeto
inline float Object::Y() const
{  return posY; }

// retorna coordenada z do objeto
inline float Object::Z() const
{  return posZ; }

// move o objeto por (deltaX, deltaY, deltaZ)
inline void Object::Translate(float dx, float dy, float dz)
{ posX += dx; posY += dy; posZ += dz; }

// move o objeto para as coordenadas (x,y,z) indicadas
inline void Object::MoveTo(float px, float py, float pz)
{ posX = px; posY = py; posZ = pz; }

// move o objeto para as coordenadas (x,y) indicadas
inline void Object::MoveTo(float px, float py)
{ posX = px; posY = py; }

// -----------------------------------------------------------------------------

#endif


