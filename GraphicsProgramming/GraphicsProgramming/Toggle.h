#pragma once
#include "glut.h"
#include <gl/gl.h>
#include <gl/glu.h>
/*toggles various openGL settings.*/
class Toggle
{
public:
	Toggle();
	~Toggle();
	void toggleBlend();//toggle on/off blending
	void toggleLit();//toggle on/off lighting
	void toggleStencil();//toggle on/off stencil
	void toggleStencilFunc();//toggle on/off stencilfunc
	void toggleDepth();//toggle on/off depth testing
	void toggleBackCull();//toggle on/off backface culling
private:
	bool blend;//true when blending is enabled
	bool lit;//true when lighting is enabled
	bool stencil;//true when stencil is enabled - not implemented
	bool func;//true when stencil func is enabled - not implemented
	bool depth;//true when depth testing is enabled
	bool cull;//true when backface culling is enabled - implemented but not used
};

