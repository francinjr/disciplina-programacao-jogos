/**********************************************************************************
// WallHit (C�digo Fonte)
//
// Cria��o:     03 Ago 2019
// Atualiza��o: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descri��o:   Efeito de explos�o de fa�scas usando sistema de part�culas
//
**********************************************************************************/

#include "GeoWars.h"
#include "MapWall.h"

// ---------------------------------------------------------------------------------

MapWall::MapWall(std::vector<Point> points)
{
	BBox(new Poly(points.data(), points.size()));
	type = MAPWALL;
}

MapWall::MapWall(Point p1, Point p2)
{
	BBox(new Rect(p1, p2));
	type = MAPWALL;
}

// ---------------------------------------------------------------------------------

void MapWall::Update()
{
}

void MapWall::Draw()
{
}

MapWall::~MapWall()
{
}
