#pragma once
#include <glut.h>
#include <gl/gl.h>
#include <gl/glu.h>
#include "Vector3.h"
#include "Shape.h"
#include "Input.h"
#include "Camera.h"
class LightBall
{
public:
	/*Create LightBall, takes specified light (eg GL_LIGHT0) as a parameter*/
	LightBall(int _light, Camera& camera);
	~LightBall();
	/*render sphere and point light at coordinates + forward vector. x y and z passed by reference to chnge the Light_Position vector in Scene.cpp*/
	void render();
	/*ball movement controls, "[" sets lightBallDistanceDec true and "]" sets lightBallDistanceInc.*/
	void checkControls(Input* input);
	/*performs rotatons and movement as outlined in checkControls()*/
	void update(float deltaTime);
	GLfloat x_;
	GLfloat y_; 
	GLfloat z_;
	Vector3 forward_;
private:
	Camera* camera_ptr;
	int light;
	bool lightBallDistanceDec;//bool is true when lightBallDistance needs to decrement.
	bool lightBallDistanceInc;//bool is true when lightBallDistance needs to increment.
	float lightBallDistance;//scalar for _forward vector. Affects LightBall's distance to position x, y, z
	Shape sphere;
};

