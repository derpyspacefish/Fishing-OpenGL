#include "lightBall.h"



LightBall::LightBall(int _light)
{
	lightBallDistance = 1.f;
	light = _light;
}


LightBall::~LightBall()
{
	glDisable(light); //disable
}

void LightBall::render(GLfloat &x, GLfloat &y, GLfloat &z, Vector3 forward)
{
	//minimum light level of 0
	GLfloat Light_Ambient[] = { 0.0f, 0.0f, 0.0f, 1.f };
	//white light
	GLfloat Light_Diffuse[] = { 0.6f, 0.6f, 1.f, 1.f };
	//multiply forward by scalar
	forward.x *= lightBallDistance;
	forward.y *= lightBallDistance;
	forward.z *= lightBallDistance;
	//add forward vector to position x y z
	x += forward.x;
	y += forward.y;
	z += forward.z;
	GLfloat Light_Position[] = {x, y, z, 1 }; //set light position to 
	glPushMatrix();
	{
		//pass light its values
		glLightfv(light, GL_AMBIENT, Light_Ambient);
		glLightfv(light, GL_DIFFUSE, Light_Diffuse);
		glLightfv(light, GL_POSITION, Light_Position);
		glLightf(light, GL_CONSTANT_ATTENUATION, 1.f);
		/*GL_LINEAR_ATTENUATION affects how dark somewhat-near objects are, while 
		GL_QUADRATIC_ATTENUATION affects how dark somewhat-far objects are.*/
		glLightf(light, GL_LINEAR_ATTENUATION, 0.125f); // not very dark
		glLightf(light, GL_QUADRATIC_ATTENUATION, 0.01f); // not dark at all
		glEnable(light); //enable
		glDisable(GL_LIGHTING);
		glPushMatrix();
		{
			glTranslatef(Light_Position[0], Light_Position[1], Light_Position[2]);
			glScalef(0.2f, 0.2f, 0.2f);
			glColor3f(1.f, 1.f, 1.f);
			sphere.renderSphere(20);
		}
		glPopMatrix();
		glEnable(GL_LIGHTING);
	}
	glPopMatrix();
}

void LightBall::checkControls(Input * input)
{
	if (input->isKeyDown('[') && lightBallDistance > 0.25f)
	{
		lightBallDistanceDec = true;
	}
	if (input->isKeyDown(']'))
	{
		lightBallDistanceInc = true;
	}
}

void LightBall::update(float deltaTime)
{
	if (lightBallDistanceDec)
	{
		lightBallDistance -= deltaTime * 2.f;
		lightBallDistanceDec = false;
	}
	if (lightBallDistanceInc)
	{
		lightBallDistance += deltaTime * 2.f;
		lightBallDistanceInc = false;
	}

}
