#ifndef _SHAPE_H
#define _SHAPE_H

#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include <math.h>

class Shape
{

public:
		void renderDisc(int segments, bool useCircleCalculation = true, int looper = 0.f);//segments determines number of triangles in disk. useCircleCalculation and looper used in bugtesting, not relevant.
		void renderSphere(int segments, int skipFromEndX = 0, int skipFromEndY = 0);
		void renderCylinder(int segments, int looper = 0.f);
		void renderCone(int segmentsX, int segmentsY, float initialRadius = 1.f, float finalRadius = -1.f);
private:
	void renderQuadMethod1();//function from the lab work, unused
	void renderQuadMethod2();//function from the lab work, unused
	void renderCubeMethod3();//function from the lab work, unused

};
#endif 
