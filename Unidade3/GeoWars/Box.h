/**********************************************************************************
// Blue (Arquivo de Cabeçalho)
//
// Criação:     10 Out 2012
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Objeto faz uma perseguição suavizada
//
**********************************************************************************/

#ifndef _GEOWARS_BOX_H_
#define _GEOWARS_BOX_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "TileSet.h"
#include "Animation.h"
#include "Drop.h"
#include "DropTypes.h"

// ---------------------------------------------------------------------------------
enum state {NORMAL, BROKEN};


class Box : public Object
{
protected:
    TileSet* tileset = nullptr;                   // folha de sprites
    Animation* anim = nullptr;                    // animacao

    TypeOfDrop typeOfDrop;


public:
    Box(float posX, float posY,TypeOfDrop type);
    ~Box();

    void OnCollision(Object* obj);      // resolução da colisão
    void Update();                      // atualização
    void Draw();                        // desenho
};


#endif