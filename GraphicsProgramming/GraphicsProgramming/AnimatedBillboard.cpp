#include "AnimatedBillboard.h"



AnimatedBillboard::AnimatedBillboard(float _startX, float _startY, float _endX, float _endY)
{			
	startX = _startX;
	startY = _startY;
	endX = _endX;
	endY = _endY;
	//glBegin(GL_QUADS);
	//glVertex3f();
	//glEnd();
}


AnimatedBillboard::~AnimatedBillboard()
{
}

void AnimatedBillboard::render()
{
}
