#pragma once
/**********************************************************************************
// Blue (Arquivo de Cabe�alho)
//
// Cria��o:     10 Out 2012
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Objeto faz uma persegui��o suavizada
//
**********************************************************************************/

#ifndef _GEOWARS_DROP_H_
#define _GEOWARS_DROP_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "DropTypes.h"

// ---------------------------------------------------------------------------------

class Drop : public Object
{
protected:
    TileSet* tileset = nullptr;
    Animation* anim = nullptr;   

    TypeOfDrop dropType;

public:
    Drop(float posX, float posY, TypeOfDrop type);
    ~Drop();

    TypeOfDrop getDropType();
    void OnCollision(Object* obj);      // resolu��o da colis�o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
};

#endif