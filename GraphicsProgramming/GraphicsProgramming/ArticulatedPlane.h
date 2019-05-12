#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include <vector>
#include "GeometryQuad.h"
//Articulated Plane by Aristophanes Yates
//Original solution, donut steel!

using namespace std;
/*
An Articulated Plane is a plane that is made up of a number of 
segments or quads. The number of quads is equal to (segments * width * segments * length).

Features (in expected order of parameters):
*	Passing no parameters will create a simple unit 1 quad.

*	Specify how many quads are desired per unit square.

*	Specify how many units wide the plane shall be.

*	Specify how many units long the plane shall be.

*	Specify the start X, start Y, end X, end Y to map the 
	specified area of a texture to the plane.

*	Passing a vector with the correct format (start X, start Y, end X, end y, next start x...) 
	before the other parameters specifies ranges of quads that shall not be created. This can be used to create holes. 

A vector that will make a 1x1 hole in the bottom left and top right will contain the following elements: 
(0, 0, 1, 1, width*segments-1, length*segments-1, width*segments, length*segments).
 */
class ArticulatedPlane : public GeometryQuad
{
public:
	ArticulatedPlane::ArticulatedPlane
(int segments = 1, int width = 1, int length = 1, float texStartX = 0, float texStartY = 0, float texEndX = 1, float texEndY = 1);
	ArticulatedPlane::ArticulatedPlane(vector<float> holeyCoordinates, int segments = 1, int width = 1, int length = 1, float texStartX = 0, float texStartY = 0, float texEndX = 1, float texEndY = 1);
	~ArticulatedPlane();
};

