// Scene class. Configures a basic 3D scene.
// Interfaces with the Input class to handle user input
// Calculates and outputs Frames Per Second (FPS) rendered.
// Important functions are the constructor (initialising the scene), 
// update (for process user input and updating scene objects) and render (renders scene).
#ifndef _SCENE_H
#define _SCENE_H

// Include GLUT, openGL, input.
#include "glut.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "Input.h"
#include <stdio.h>
// Further includes should go here:
#include "SOIL.h"
#include <vector>
#include "Camera.h"
#include "Shape.h"
#include "Model.h"
#include "ArticulatedPlane.h"
#include "Shadow.h"
#include "Prop.h"
#include "CameraLord.h"
#include "Toggle.h"

class Scene {

public:
	Scene(Input *in);
	// Main render function
	void render();
	// Handle input function that receives delta time from parent.
	void handleInput(float dt);
	// Update function receives delta time from parent (used for frame independent updating).
	void update(float dt);
	// Resizes the OpenGL output based on new window size.
	void resize(int w, int h);

protected:
	void skyBox(int x, int y, int z);
	// Renders text (x, y positions, RGB colour of text, string of text to be rendered)
	void displayText(float x, float y, float r, float g, float b, char* string);
	// A function to collate all text output in a single location
	void renderTextOutput();
	void calculateFPS();

	// draw primitive functions


	// For access to user input.
	Input* input;

	// For access to model loader.
	Model model[1];

	// For Window and frustum calculation.
	int width, height;
	float fov, nearPlane, farPlane;

	// For FPS counter and mouse coordinate output.
	int frame = 0, time, timebase = 0;
	char fps[40];
	char mouseText[40];

	//input bools
	bool wireToggle;
	bool noRotate;
	bool cameraSwitchLightBall;
	bool cameraSwitchNormal;
	bool paused;

	float rotation;
	float rotSpeed;
	//textures
	GLuint beamTexture;
	GLuint skyboxTexture;
	GLuint reflectedSkyboxTexture;
	GLuint dogeTexture;
	GLuint idolFaceTexture;

	float boxTexSize; //Width or height of the skybox texture (they are the same). 1 divided by this number for the x and y coordinates gives the top left corner of the pixel second from the top and second pixel from the left.This can be multiplied to give the top left corner of any pixel
	float boxSideTexSize; //Width or height of the texture of the texture segment used for 1 face (they are the same).
	float boxIteratorX;
	float boxIteratorY;
	CameraLord cameraLord;


	int previousMouseX;
	int previousMouseY;
	int deltaMouseX; //change in mouse x coord
	int deltaMouseY; //change in mouse y coord
	int cameraIndex;//used for camera switching. Specifies a camera.
	float shadowMatrix[16];
	Shadow shadowMan;
	ArticulatedPlane* articulatePlaneHandler;
	Prop prop; //collection scene props. Contains articulated planes, spotlights, and lightballs
	Toggle* toggle; //toggles various openGL settings

	Shape shape_handler;
};

#endif