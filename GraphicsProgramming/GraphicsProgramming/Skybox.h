#pragma once


#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>

#include "Toggle.h"
#include "CameraLord.h"
#include "SOIL.h"

class worldSkyBox
{
public:
	worldSkyBox();
	~worldSkyBox();
	void skyBoxRun(int x, int y, int z, Toggle* &toggle, CameraLord &cameraLord, int &cameraIndex, float &rotation);

protected:
	float boxTexSize; //Width or height of the skybox texture (they are the same). 1 divided by this number for the x and y coordinates gives the top left corner of the pixel second from the top and second pixel from the left.This can be multiplied to give the top left corner of any pixel
	float boxSideTexSize; //Width or height of the texture of the texture segment used for 1 face (they are the same).
	float boxIteratorX;
	float boxIteratorY;

	GLuint skyboxTexture;
	GLuint reflectedSkyboxTexture;

};
