#pragma once

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "GeometryQuad.h"
class Sphere : public GeometryQuad
{
public:
	Sphere(int division, int skipFromEndX = 0, int skipFromEndY = 0);
	~Sphere();
};

