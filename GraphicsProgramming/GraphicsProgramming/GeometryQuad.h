#pragma once
#include "Geometry.h"
/*

Inherited properties:
a personal texture
vectors of xyz coords for normals, textures, and vertices
Inherited functions:
can bind personal texture to object

Functions:
render an object according to coordinate vectors
*/
class GeometryQuad : public Geometry 
{
public:
	GeometryQuad();
	~GeometryQuad();
	void render();
};

