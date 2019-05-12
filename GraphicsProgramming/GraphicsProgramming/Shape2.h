
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
#include <math.h>

class Shape2
{

public:
		void renderDisc(int segments, bool useCircleCalculation = true, int looper = 0.f);
		void renderSphere(int division, int skipFromEndX = 0, int skipFromEndY = 0);
		void render6(int segments, int looper = 0.f);
		void render7(int segments, float initialRadius = 1.f, float finalRadius = -1.f);
private:
	void renderQuadMethod1();//function from the lab work, unused
	void renderQuadMethod2();//function from the lab work, unused
	void renderCubeMethod3();//function from the lab work, unused

};
