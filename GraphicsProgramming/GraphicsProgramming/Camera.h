#pragma once
#include "Vector3.h"
class Camera
{
public:
	Camera(float _cameraSpeed);
	~Camera();
	float cameraSpeed;
	float Pitch;
	float Yaw;
	float Roll;
	float MaxPitch;
	float MaxYaw;
	float MaxRoll;
	float MinPitch;
	float MinYaw;
	float MinRoll;
	//standard boolean variables that are set when certain keys are pushed. See CameraLord.
	bool cameraGoingForward;
	bool cameraGoingBack;
	bool cameraGoingLeft;
	bool cameraGoingRight;
	bool cameraGoingUp;
	bool cameraGoingDown;
	bool yawInc;
	bool yawDec;
	bool pitchInc;
	bool pitchDec;
	bool rollInc;
	bool rollDec;
	float getPosX();
	float getPosY();
	float getPosZ();
	float getLookX();
	float getLookY();
	float getLookZ();
	float getUpX();
	float getUpY();
	float getUpZ();
	float Camera::getYaw();
	float Camera::getPitch();
	float Camera::getRoll();
	Vector3 getForward();
	/*setter for position vector*/
	void setPos(float _x, float _y, float _z);
	/*setter for yaw pitch and roll*/
	void setOrientation(float _yaw, float _pitch, float _roll);
	void moveForward(float amount);
	void moveRight(float amount);
	void moveUp(float amount);
	void update();
private:
	Vector3 lookat;
	Vector3 position;
	Vector3 forward;
	Vector3 up;
	Vector3 right;
};

