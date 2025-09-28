/**********************************************************************************
// WallHit (Arquivo de Cabe�alho)
//
// Cria��o:     03 Ago 2019
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Efeito de explos�o de fa�scas usando sistema de part�culas
//
**********************************************************************************/

#ifndef _GEOWARS_MAPWALL_H_
#define _GEOWARS_MAPWALL_H_

// ---------------------------------------------------------------------------------

#include "Object.h"    
#include "Types.h"
#include <vector>


// ---------------------------------------------------------------------------------

class MapWall : public Object
{
private:

public:
    MapWall(std::vector<Point> points);        // construtor
    MapWall(Point p1, Point p2);        // construtor
    ~MapWall();                         // destrutor                      

    // ---------------------------------------------------------------------------------
    void Update();                      // atualiza��o
    void Draw();                        // desenho

    // ---------------------------------------------------------------------------------
};

#endif