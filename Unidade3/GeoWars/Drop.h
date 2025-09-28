#pragma once
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
    void OnCollision(Object* obj);      // resolução da colisão
    void Update();                      // atualização
    void Draw();                        // desenho
};

#endif