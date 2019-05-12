#include "Toggle.h"



Toggle::Toggle()
{
	blend	= false;
	lit		= false;
	stencil	= false;
	func	= false;
	depth	= false;
}


Toggle::~Toggle()
{
}

void Toggle::toggleBlend()
{
	if (!blend)
	{
		glEnable(GL_BLEND);
		blend = true;
	}
	else
	{
		glDisable(GL_BLEND);
		blend = false;
	}
}

void Toggle::toggleLit()
{
	if (!lit)
	{
		glEnable(GL_LIGHTING);
		lit = true;
	}
	else
	{
		glDisable(GL_LIGHTING);
		lit = false;
	}
}

void Toggle::toggleStencil()
{
}

void Toggle::toggleStencilFunc()
{
}

void Toggle::toggleDepth()
{
	if (!depth)
	{
		glEnable(GL_DEPTH_TEST);
		depth = true;
	}
	else
	{
		glDisable(GL_DEPTH_TEST);
		depth = false;
	}
}

void Toggle::toggleBackCull()
{
	if (!cull)
	{
		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		cull = true;
	}
	else
	{
		glDisable(GL_CULL_FACE);
		cull = false;
	}
}
