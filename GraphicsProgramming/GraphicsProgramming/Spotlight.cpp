#include "Spotlight.h"


Spotlight::Spotlight(int _light, Toggle* _toggle)
{
	light = _light;
	roll = 0.f;
	pitch = 0.f;
	rotationSpeed = 0.5f;
	lightRotDirectionPitch = 1.f;
	lightRotDirectionRoll = 1.f;
	toggle = _toggle;
}

Spotlight::~Spotlight()
{
	glDisable(light);
}

void Spotlight::update(float deltaTime)
{
	/*
	if pitch or roll is out of bounds, make scalar a random number (5 to 10) in the direction
	opposite of the bound
	*/
	if (pitch > (45.f * 0.5f))	
	{
		lightRotDirectionPitch = (float)(rand() % 5) + 5;
		lightRotDirectionPitch *= -1.f;
	}
	if (pitch < (-45.f * 0.5f))
	{
		lightRotDirectionPitch = (float)(rand() % 5) + 5;
	}
	if (roll >(45.f * 0.5f))
	{
		lightRotDirectionRoll = (float)(rand() % 5) + 5;
		lightRotDirectionRoll *= -1.f;
	}
	if (roll < (-45.f * 0.5f))
	{
		lightRotDirectionRoll = (float)(rand() % 5) + 5;
	}

	//add to roll and pitch accordingly
	roll += deltaTime * rotationSpeed * lightRotDirectionRoll;
	pitch += deltaTime * rotationSpeed * lightRotDirectionPitch;
}


void Spotlight::render(float x, float y, float z)
{
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glRotatef(roll, 0, 0, 1);
		glRotatef(pitch, 1, 0, 0);
		textureBind(texture);
		/*cone within a cylinder*/
		shape.renderCylinder(10.f);
		shape.renderCone(10.f, 100.f, 10.f, 0.f);
		glPushMatrix();
		{
			glScalef(0.6f, 0.6f, 0.6f);
			shape.renderSphere(20.f);
		}
		glPopMatrix();
		toggle->toggleBlend();
		toggle->toggleLit();
		glPushMatrix();
		{
			glTranslatef(0.f, 1.f, 0.f);
			glScalef(1.f, 15.f, 1.f);
			textureBind(beamTexture);
			shape.renderCone(10.f, 1.f, 5.f, 15.f); //light beam
		}
		glPopMatrix();
		toggle->toggleLit();
		toggle->toggleBlend();
		GLfloat Light_Ambient2[] = { 0.f, 0.f, 0.f, 1.f }; //minimum light level FOR ENTIRE SCENE
		GLfloat Light_Diffuse2[] = { 1.0f, 1.0f, 1.0f, 1.0f }; //colour of light
		GLfloat Light_Position2[] = { 0.0f, 0.0f, 1.0f, 1.0f }; //placed just above the cylinder
		GLfloat spot_Direction[] = { 0.0f, 1.0f, 0.0f }; //direction of spot light up

		glLightfv(light, GL_AMBIENT, Light_Ambient2);
		glLightfv(light, GL_DIFFUSE, Light_Diffuse2);
		glLightfv(light, GL_POSITION, Light_Position2);
		glLightf(light, GL_SPOT_CUTOFF, 25.0f); // angle of light cone
		glLightfv(light, GL_SPOT_DIRECTION, spot_Direction);
		glLightf(light, GL_SPOT_EXPONENT, 50.0);// light strength
		glEnable(light);
	}
	glPopMatrix();
}

void Spotlight::renderFake(float x, float y, float z)
{
	//as render() but without the actual light.
	glPushMatrix();
	{
		glTranslatef(x, y, z);
		glRotatef(roll, 0, 0, 1);
		glRotatef(pitch, 1, 0, 0);
		textureBind(texture);
		shape.renderCylinder(10.f);
		//glColor4f(0.8f, 0.8f, 1.0f, 0.8f);
		toggle->toggleBlend();
		toggle->toggleLit();
		glPushMatrix();
		{
			glTranslatef(0.f, 1.f, 0.f);
			glScalef(1.f, 15.f, 1.f);
			textureBind(beamTexture);
			shape.renderCone(10.f, 1.f, 5.f, 15.f);
		}
		glPopMatrix();
		toggle->toggleLit();
		toggle->toggleBlend();
	}
	glPopMatrix();
}

void Spotlight::setTexture(GLuint _beamTexture, GLuint _texture)//overloaded from Geometry
{
	beamTexture = _beamTexture;
	texture = _texture;
}
