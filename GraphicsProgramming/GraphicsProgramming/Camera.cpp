#include "Camera.h"

Camera::Camera(float _cameraSpeed)
{
	Pitch = 0.f;
	Yaw = 0.f;
	Roll = 0.f;
	cameraSpeed = _cameraSpeed;

	MaxPitch = 60;
	MaxYaw = 1;
	MaxRoll = 1;
	MinPitch = -50;
	MinYaw = -1;
	MinRoll = -1;

	setPos(0, 0, 0);
}

Camera::~Camera()
{
}


//get position
	float Camera::getPosX()
	{
		return position.getX();
	}
	float Camera::getPosY()
	{
		return position.getY();
	}
	float Camera::getPosZ()
	{
		return position.getZ();
	}
//get look at
	float Camera::getLookX()
	{
		return lookat.getX();
	}
	float Camera::getLookY()
	{
		return lookat.getY();
	}
	float Camera::getLookZ()
	{
		return lookat.getZ();
	}
//get up
	float Camera::getUpX()
	{
		return up.getX();
	}
	float Camera::getUpY()
	{
		return up.getY();
	}
	float Camera::getUpZ()
	{
		return up.getZ();
	}
//get forward vector
	Vector3 Camera::getForward()
	{
		return forward;
	}
//set position
	void Camera::setPos(float _x, float _y, float _z)
	{
		position.set(_x, _y, _z);
		return;
	}

//set yaw pitch and roll
	void Camera::setOrientation(float _yaw, float _pitch, float _roll)
	{
		Yaw = _yaw;
		Pitch = _pitch;
		Roll = _roll;
	}

	//get Yaw, Pitch, Roll
	float Camera::getYaw()
	{
		return Yaw;
	}
	float Camera::getPitch()
	{
		return Pitch;
	}
	float Camera::getRoll()
	{
		return Roll;
	}

//move forward
	void Camera::moveForward(float amount)
	{
		position.add (forward, amount);
	}
//move right
	void Camera::moveRight(float amount)
	{
		position.add(right, amount);
	}
//move up
	void Camera::moveUp(float amount)
	{
		position.add(up, amount);
	}

void Camera::update()
{
	float cosR, cosP, cosY; //temp values for sin/cos from
	float sinR, sinP, sinY;

	// Roll, Pitch and Yall are variables stored by the camera
	// handle rotation
	// Only want to calculate these values once, when rotation changes, not every frame.
	cosY = cosf(Yaw*3.1415f / 180);
	cosP = cosf(Pitch*3.1415f / 180);
	cosR = cosf(Roll*3.1415f / 180);

	sinY = sinf(Yaw*3.1415f / 180);
	sinP = sinf(Pitch*3.1415f / 180);
	sinR = sinf(Roll*3.1415f / 180);

	//This using the parametric equation of a sphere
	// Calculate the three vectors to put into glu Lookat
	// Look direction, position and the up vector
	// This function could also calculate the right vector
	forward.x = sinY * cosP;
	forward.y = sinP;
	forward.z = cosP * -cosY;

	// Look At Point
	// To calculate add Forward Vector to Camera position.
	lookat = forward + position;

	// Up Vector
	up.x = -cosY * sinR - sinY * sinP * cosR;
	up.y = cosP * cosR;
	up.z = -sinY * sinR - sinP * cosR * -cosY;

	// Side Vector (right)
	// this is a cross product between the forward and up vector.
	// If you don’t need to calculate this, don’t do it.
	right = up.cross(forward);
}