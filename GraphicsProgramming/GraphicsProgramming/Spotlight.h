#pragma once
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Shape.h"
#include "GeometryQuad.h"
#include "Toggle.h"
class Spotlight : public GeometryQuad
{
public:
	/*Create spotlight, takes specified light (eg GL_LIGHT0) as a parameter*/
	Spotlight(int _light, Toggle* _toggle);
	~Spotlight();
	/*continue light animation*/
	void update(float deltaTime);
	/*Renders spotlight at the origin or the paremeters given (x, y, z)*/
	void render(float x = 0, float y = 0, float z = 0);
	/*Renders spotlight (only geometry) at the origin or the paremeters given (x, y, z)*/
	void renderFake(float x, float y, float z);
	void setTexture(GLuint _beamTexture, GLuint _texture);
private:
	int light;
	float rotationSpeed;
	float pitch;//pitch angle of light (from a default angle of 0 degrees from positive Y)
	float roll;//pitch angle of light (from a default angle of 0 degrees from positive Y)
	float lightRotDirectionRoll; // scalar for the angle added to roll. Affects speed as well as direction
	float lightRotDirectionPitch; // scalar for the angle added to pitch. Affects speed as well as direction
	GLuint beamTexture;
	Shape shape;
	Toggle* toggle;
};

