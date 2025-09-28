/**********************************************************************************
// WallHit (Arquivo de Cabeçalho)
//
// Criação:     03 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Efeito de explosão de faíscas usando sistema de partículas
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
    void Update();                      // atualização
    void Draw();                        // desenho

    // ---------------------------------------------------------------------------------
};

#endif