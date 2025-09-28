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

    void OnCollision(Object* obj);      // resolu��o da colis�o
    void Update();                      // atualiza��o
    void Draw();                        // desenho
};


#endif