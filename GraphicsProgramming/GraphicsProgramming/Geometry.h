#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <vector>
/*
inheritors:
GeometryQuad and GeometryTri
*/


/*
Properties:
a personal texture
vectors of xyz coords for normals, textures, and vertices
Functions:
can bind personal texture to object
*/
class Geometry
{
public:
	Geometry();
	~Geometry();
	void setTexture(GLuint _texture);//setter for texture
protected:
	GLuint texture;//a personal texture for an object
	std::vector<float>	normXYZ;//vector of xyz normal coordinates. Stored in form "X Y Z X Y Z".
	std::vector<float>	texXY;//vector of xyz texture coordinates. Stored in form "X Y Z X Y Z".
	std::vector<float>	vertXYZ;//vector of xyz vertex coordinates. Stored in form "X Y Z X Y Z".
	void textureBind();//binds personal texture to object
	void textureBind(GLuint _texture);//binds a specified texture to object. Useful for objects made of multiple shapes.
};

