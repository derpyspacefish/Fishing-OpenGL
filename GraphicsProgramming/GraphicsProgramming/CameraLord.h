#pragma once
#include "Camera.h"
#include <vector>
#include "Input.h"
#include "glut.h"
/*Camera manager, manages cameras.*/
class CameraLord
{
public:
	CameraLord();
	~CameraLord();

	/*Camera movement controls*/
	void checkControls(Input* _input, float _previousMouseX, float _previousMouseY, int _cameraIndex);
	void newCamera(float _cameraSpeed = 1.f);

	/*Updates indicated camera, performing rotatons and movement as outlined in checkControls()*/
	void update(float dt, float _deltaMouseX, float _deltaMouseY, int _cameraIndex);

	/*returns a pointer to the camera at specified index*/
	Camera* getCamera(int index);

private:
	std::vector<Camera*> cameras;
};

