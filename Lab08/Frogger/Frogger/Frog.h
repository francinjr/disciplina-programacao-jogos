/**********************************************************************************
// Frog (Arquivo de Cabe�alho)
// 
// Cria��o:     19 Dez 2012
// Atualiza��o: 19 Mai 2025
// Compilador:  Visual C++ 2022
//
// Descri��o:   Sapo do jogo Frogger
//
**********************************************************************************/

#ifndef _FROGGER_FROG_H_
#define _FROGGER_FROG_H_

// ---------------------------------------------------------------------------------
// Inclus�es

#include "Types.h"             // tipos espec�ficos da engine
#include "Object.h"            // interface de object
#include "Sprite.h"            // interface de sprites

// ---------------------------------------------------------------------------------

class Frog : public Object
{
private:
    Sprite * sprite;

public:
    Frog();
    ~Frog();

    void Update();
    void Draw();
};

// ---------------------------------------------------------------------------------
// Fun��es Membro Inline

inline void Frog::Draw()
{ sprite->Draw(x,y,z); }

// ---------------------------------------------------------------------------------

#endif