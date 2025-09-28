/**********************************************************************************
// WallHit (Código Fonte)
//
// Criação:     03 Ago 2019
// Atualização: 01 Nov 2021
// Compilador:  Visual C++ 2022
//
// Descrição:   Efeito de explosão de faíscas usando sistema de partículas
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
