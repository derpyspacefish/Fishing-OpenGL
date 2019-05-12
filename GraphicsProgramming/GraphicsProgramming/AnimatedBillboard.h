#pragma once
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Vector3.h"
#include <vector>
class AnimatedBillboard
{
public:
	AnimatedBillboard(float _startX = 0.f, float _startY = 0.f, float _endX = 1.f, float _endY = 1.f);
	~AnimatedBillboard();
	void render();
private:
	float startX;
	float startY;
	float endX;
	float endY;
	float xOffset;
	float yOffset;
};

