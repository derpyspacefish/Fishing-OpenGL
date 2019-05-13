#include "lightBall.h"



LightBall::LightBall(int _light, Camera& camera)
{
	lightBallDistance = 1.f;
	light = _light;
	camera_ptr = &camera;
}


LightBall::~LightBall()
{
	glDisable(light); //disable
}

void LightBall::render()
{
	x_ = camera_ptr->getPosX();
	y_ = camera_ptr->getPosY();
	z_ = camera_ptr->getPosZ();
	forward_ = camera_ptr->getForward();
	//minimum light level of 0
	GLfloat Light_Ambient[] = { 0.0f, 0.0f, 0.0f, 1.f };
	//white light
	GLfloat Light_Diffuse[] = { 0.6f, 0.6f, 1.f, 1.f };
	//multiply forward by scalar
	forward_.x *= lightBallDistance;
	forward_.y *= lightBallDistance;
	forward_.z *= lightBallDistance;
	//add forward vector to position x y z
	x_ += forward_.x;
	y_ += forward_.y;
	z_ += forward_.z;
	GLfloat Light_Position[] = {x_, y_, z_, 1 }; //set light position to 
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
