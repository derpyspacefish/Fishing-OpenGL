#include "CameraLord.h"


CameraLord::CameraLord()
{
}


CameraLord::~CameraLord()
{
	for (auto it : cameras)
	{
		delete it;
	}
}

void CameraLord::checkControls(Input * _input, float _previousMouseX, float _previousMouseY, int _camIndicater)
{	
	//yaw - j to l
	{
		//yaw left
		if (_input->isKeyDown('j') || _previousMouseX > _input->getMouseX())
		{
			getCamera(_camIndicater)->yawDec = true;

		}
		else
		{
			getCamera(_camIndicater)->yawDec = false;
		}

		//yaw right
		if (_input->isKeyDown('l') || _previousMouseX < _input->getMouseX())
		{
			getCamera(_camIndicater)->yawInc = true;

		}
		else
		{
			getCamera(_camIndicater)->yawInc = false;
		}
	}

	//pitch - k to i
	{
		//pitch up
		if (_input->isKeyDown('i') || _previousMouseY > _input->getMouseY())
		{
			getCamera(_camIndicater)->pitchInc = true;

		}
		else
		{
			getCamera(_camIndicater)->pitchInc = false;
		}

		//pitch down
		if (_input->isKeyDown('k') || _previousMouseY < _input->getMouseY())
		{
			getCamera(_camIndicater)->pitchDec = true;
		}
		else
		{
			getCamera(_camIndicater)->pitchDec = false;
		}
	}

	//roll - u to o
	{
		//roll left
		if (_input->isKeyDown('u'))
		{
			getCamera(_camIndicater)->rollDec = true;
		}
		else
		{
			getCamera(_camIndicater)->rollDec = false;
		}

		//roll right
		if (_input->isKeyDown('o'))
		{
			getCamera(_camIndicater)->rollInc = true;

		}
		else
		{
			getCamera(_camIndicater)->rollInc = false;
		}
	}

	//camera translation - w,s,a,d for horizontal movement and space,c for vertical
	{
		//camera forward
		{
			if (_input->isKeyDown('w') || _input->isKeyDown('W'))
			{
				getCamera(_camIndicater)->cameraGoingForward = true;

			}
			else
			{
				getCamera(_camIndicater)->cameraGoingForward = false;
			}
		}
		//camera back
		{
			if (_input->isKeyDown('s') || _input->isKeyDown('S'))
			{
				getCamera(_camIndicater)->cameraGoingBack = true;

			}
			else
			{
				getCamera(_camIndicater)->cameraGoingBack = false;
			}
		}
		//camera right
		{
			if (_input->isKeyDown('d') || _input->isKeyDown('D'))
			{
				getCamera(_camIndicater)->cameraGoingRight = true;

			}
			else
			{
				getCamera(_camIndicater)->cameraGoingRight = false;
			}
		}
		//camera left
		{
			if (_input->isKeyDown('a') || _input->isKeyDown('A'))
			{
				getCamera(_camIndicater)->cameraGoingLeft = true;

			}
			else
			{
				getCamera(_camIndicater)->cameraGoingLeft = false;
			}
		}
		//camera up
		{
			if (_input->isKeyDown(' '))
			{
				getCamera(_camIndicater)->cameraGoingUp = true;

			}
			else
			{
				getCamera(_camIndicater)->cameraGoingUp = false;
			}
		}
		//camera down
		{
			if (_input->isKeyDown('c'))
			{
				getCamera(_camIndicater)->cameraGoingDown = true;

			}
			else
			{
				getCamera(_camIndicater)->cameraGoingDown = false;
			}
		}
	}
}

void CameraLord::newCamera(float _cameraSpeed)
{
	Camera* camera = new Camera(_cameraSpeed);
	cameras.push_back(camera);
	return;
}

void CameraLord::update(float dt, float _deltaMouseX, float _deltaMouseY, int _cameraIndicator)
{
	if (_deltaMouseX < 100 && _deltaMouseY < 100)
	{
		//camera rotation
		Camera* it = cameras[_cameraIndicator];
		if (it->yawDec)
		{
			it->Yaw = it->Yaw - it->cameraSpeed * dt * (1 + abs(_deltaMouseX));
		}
		if (it->yawInc)
		{
			it->Yaw = it->Yaw + it->cameraSpeed * dt * (1 + abs(_deltaMouseX));
		}
		if (it->pitchDec)
		{
			if (it->Pitch > it->MinPitch)
				it->Pitch = it->Pitch - it->cameraSpeed * dt * (1 + abs(_deltaMouseY));
		}
		if (it->pitchInc)
		{
			/*if (it->Pitch > it->MaxPitch * 2  || it->Pitch < it->MinPitch * 2)
				it->setOrientation(0, 0, 0);*/

			if (it->Pitch < it->MaxPitch)
				it->Pitch = it->Pitch + it->cameraSpeed * dt * (1 + abs(_deltaMouseY));
		}

		if (it->rollDec)
		{
			it->Roll = it->Roll + it->cameraSpeed * dt;
		}
		if (it->rollInc)
		{
			it->Roll = it->Roll - it->cameraSpeed * dt;
		}


		//camera translation
		if (it->cameraGoingForward)
		{
			it->moveForward(+(it->cameraSpeed * dt));
		}
		if (it->cameraGoingBack)
		{
			it->moveForward(-(it->cameraSpeed * dt));
		}
		if (it->cameraGoingRight)
		{
			it->moveRight(-(it->cameraSpeed * dt));
		}
		if (it->cameraGoingLeft)
		{
			it->moveRight(+(it->cameraSpeed * dt));
		}
		if (it->cameraGoingUp)
		{
			it->moveUp(+(it->cameraSpeed * dt));
		}
		if (it->cameraGoingDown)
		{
			it->moveUp(-(it->cameraSpeed * dt));
		}
		it->update();
	}
}

Camera * CameraLord::getCamera(int index)
{
	return cameras.at(index);
}

