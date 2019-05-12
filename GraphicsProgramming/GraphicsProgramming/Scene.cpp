#include "Scene.h"
#include <iostream>
#define TextureCoordX (boxIteratorX * boxSideTexSize - boxSideTexSize) / boxTexSize
#define TextureCoordY (boxIteratorY * boxSideTexSize - boxSideTexSize) / boxTexSize
#define part1 boxIteratorY++
#define part2 boxIteratorX++
#define part3 boxIteratorY--
/*
These defines were used to create the rubix cube in the labs. They are now used in my skybox functions.
*/

//Find more comments in the header file!




// Scene constructor, initilises OpenGL
// You should add further variables to need initilised.
Scene::Scene(Input *in)
{
	toggle = new Toggle;
	// Store pointer for input class
	input = in;

	//OpenGL settings
	glShadeModel(GL_SMOOTH);							// Enable Smooth Shading
	glClearColor(0.39f, 0.58f, 93.0f, 1.0f);			// Cornflour Blue Background
	glClearDepth(1.0f);									// Depth Buffer Setup
	glClearStencil(0);									// Clear stencil buffer
	//glEnable(GL_DEPTH_TEST);							// Enables Depth Testing
	toggle->toggleDepth();
	//glEnable(GL_LIGHTING);
	toggle->toggleLit();
	glDepthFunc(GL_LEQUAL);								// The Type Of Depth Testing To Do
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);	// Really Nice Perspective Calculations

														// Other OpenGL / render setting should be applied here.

	model[0].load("models/shibainu.obj", "gfx/shibatexture.png"); //dog
	model[1].load("models/Tyrion Lannister 3D Model.obj", "gfx/Smooth white marble.jpg"); //statue
	model[2].load("models/snek.obj", "gfx/snek.png"); // golden snake

	// Initialise scene variables
	{
		boxTexSize = 1024.f;
		boxSideTexSize = 256.f;
		noRotate = true;
		wireToggle = false;
		rotSpeed = 5.f;
		rotation = 0.f;
		cameraIndex = 0;
		previousMouseX = 0;
		previousMouseY = 0;
		deltaMouseX = 0;
		deltaMouseY = 0;
		paused = true;
	}


	//load textures
	{
		beamTexture = SOIL_load_OGL_texture
		(
			"gfx/lightRay.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
		skyboxTexture = SOIL_load_OGL_texture
		(
			"gfx/skybox.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		reflectedSkyboxTexture = SOIL_load_OGL_texture
		(
			"gfx/skyboxEasterEgg.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		dogeTexture = SOIL_load_OGL_texture
		(
			"gfx/doge.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);

		idolFaceTexture = SOIL_load_OGL_texture
		(
			"gfx/idol.png",
			SOIL_LOAD_AUTO,
			SOIL_CREATE_NEW_ID,
			SOIL_FLAG_MIPMAPS | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
		);
	}

	// Initialise scene objects
	{
		cameraLord.newCamera();// accessed by a vector contained within cameraLord, index 0
		cameraLord.newCamera();//index 1
		cameraLord.newCamera();//index 2


		for (int i = 0; i < 3; i++)
		{
			cameraLord.getCamera(i)->setPos(0.f, 0.f, 6.f);
		}
		cameraLord.getCamera(1)->setPos(-6.f, 6.f, 0.f);
		cameraLord.getCamera(1)->Yaw = 75;
		cameraLord.getCamera(1)->Roll = 0;

		//props and articulated planes
		prop.newSpotlight(GL_LIGHT1, toggle);
		prop.newSpotlight(GL_LIGHT2, toggle);
		prop.getSpotlight(0)->setTexture(beamTexture, dogeTexture);
		prop.getSpotlight(1)->setTexture(beamTexture, dogeTexture);
		prop.newLightBall(GL_LIGHT0);
		vector<float> holeyCoords;
		for (int holeY = 0; holeY < 5; holeY++)
		{
			for (int holeX = 0; holeX < 17; holeX++)
			{
				holeyCoords.push_back(holeX * 5 + 0.f + holeX);
				holeyCoords.push_back(holeY * 5 + 5.f + holeY);
				holeyCoords.push_back(holeX * 5 + 5.f + holeX);
				holeyCoords.push_back(holeY * 5 + 10.f + holeY);
			}
		}


		holeyCoords.push_back(20.f);
		holeyCoords.push_back(100.f);
		holeyCoords.push_back(40.f);
		holeyCoords.push_back(110.f);

		prop.newPlane(holeyCoords, 5, 10, 50, 660.f/1024.f, 330.f/1024.f, 100.f / 1024.f, 1.f - 330.f / 1024.f); //element 0
		prop.newPlane(1, 20, 20); // element 1
		prop.newPlane(1, 20, 20); // element 2
		prop.newPlane(5, 100, 100); // element 3
		prop.getPlane(0)->setTexture(dogeTexture);
		prop.getPlane(2)->setTexture(dogeTexture);
		prop.getPlane(3)->setTexture(dogeTexture);
	}

	glutSetCursor(GLUT_CURSOR_NONE);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);
	//glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glClearStencil(0);
	//load models
}

void Scene::handleInput(float dt)
{
	/*
	basic controls
	w s a d for cardinal movement, c to go down, space to go up
	i j k l or mouse movement to rotate camera using yaw and pitch, u and o for mouse roll rotation
	y to reset camera to corridor
	h and n to switch between light ball camera and normal camera.
	] and [ to move lightball forward or back
	r for wireframe mode
	g to cause skybox and statue to rotate (opposing directions)


	some controls are handled by the object to which they are relevant by the function "checkControls"
	*/
	if (dt > 10.f)//upper bound of delta time
	{
		dt = 10.f;
	}
	deltaMouseX = input->getMouseX() - previousMouseX;
	deltaMouseY = input->getMouseY() - previousMouseY;
	// Handle user input
	prop.getLightBall(0)->checkControls(input);
	//reset cam
	{
		if (input->isKeyDown('y'))
		{
			//new looking position is down and to the left
			cameraLord.getCamera(cameraIndex)->setOrientation((-10.f / 2), (-10.f / 2), (0));
			cameraLord.getCamera(cameraIndex)->setPos(-9.f / 2, -9.f / 2, -30.f);
			input->SetKeyUp('y');
		}
	}
	//wireframe - r toggle
	{
		if (input->isKeyDown('r') && wireToggle == false)
		{
			glPolygonMode(GL_FRONT, GL_LINE);
			//glPolygonMode(GL_BACK, GL_LINE);
			input->SetKeyUp('r');
			wireToggle = true;
		}
		else if (input->isKeyDown('r') && wireToggle == true)
		{
			glPolygonMode(GL_FRONT, GL_FILL);
			//glPolygonMode(GL_BACK, GL_FILL);
			input->SetKeyUp('r');
			wireToggle = false;
		}
	}
	//rotate skybox - g toggle
	{
		if (input->isKeyDown('g') && noRotate == false)
		{
			noRotate = true;
			input->SetKeyUp('g');
		}
		else if (input->isKeyDown('g') && noRotate == true)
		{
			noRotate = false;
			input->SetKeyUp('g');
		}
	}

	//switch camera
	{
		if (input->isKeyDown('h'))
		{
			cameraSwitchLightBall = true;
			cameraSwitchNormal = false;
			input->SetKeyUp('h');
		}
		else if (input->isKeyDown('n'))
		{
			cameraSwitchNormal = true;
			cameraSwitchLightBall = false;
			input->SetKeyUp('n');
		}
	}

	cameraLord.checkControls(input, previousMouseX, previousMouseY, cameraIndex);

	previousMouseX = input->getMouseX();
	previousMouseY = input->getMouseY();
}

void Scene::update(float dt)
{
	if (dt > 10.f)
	{
		dt = 10.f;
	}
	// update scene related variables.
	// Calculate FPS for output
	calculateFPS();
	cameraIndex = 0;
	if (cameraSwitchNormal)
	{
		cameraIndex = 0;
	}
	if (cameraSwitchLightBall)
	{
		cameraIndex = 1;
	}
	if (noRotate == false)
	{
		rotation = rotation + rotSpeed * dt;
	}
	cameraLord.update(dt, deltaMouseX, deltaMouseY, cameraIndex);
	prop.getSpotlight(0)->update(dt);
	prop.getSpotlight(1)->update(dt);
	prop.getLightBall(0)->update(dt);
}
/*renders at camera position
x, y, and z components may be scaled to be consistant with reflection*/
void Scene::skyBox(int x = 1, int y = 1, int z = 1) //x, y, and z are position scalars
{
	glPushMatrix();
	{
		toggle->toggleLit();
		//glDisable(GL_LIGHTING);
		toggle->toggleDepth();
		//glDisable(GL_DEPTH_TEST);
		//
		glTranslatef(cameraLord.getCamera(cameraIndex)->getPosX() * x, cameraLord.getCamera(cameraIndex)->getPosY() * y, cameraLord.getCamera(cameraIndex)->getPosZ() * z);
		glRotatef(rotation, 0.f, -1.f, 0.f);
		//cube 1
		//						   +--------+
		//						  /        /|
		//						 /        / |
		//						+--------+  |
		//						|        |  |
		//						|        |  +
		//						|        | /
		//						|        |/
		//						+--------+

		glColor3f(1, 1, 1);
		//face front
		boxIteratorX = 1.f;
		boxIteratorY = 2.f;
		glBindTexture(GL_TEXTURE_2D, skyboxTexture);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glBegin(GL_QUADS);


		glTexCoord2f(TextureCoordX, TextureCoordY);
		part1;
		glVertex3f(-1.f, 1.f, 1.f);

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, -1.f, 1.f);
		part2;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, -1.f, 1.f);
		part3;

		/*
		part1, part2, part3, TextureCoordX, and TextureCoordY is just me being "clever" with #define because rendering a cube is a very repetitive process.
		what each #define means is pasted here for your convenience

		TextureCoordX: (boxIteratorX * boxSideTexSize - boxSideTexSize) / boxTexSize
		TextureCoordY: (boxIteratorY * boxSideTexSize - boxSideTexSize) / boxTexSize
		part1: boxIteratorY++
		part2: boxIteratorX++
		part3: boxIteratorY--
		*/

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, 1.f, 1.f);

		//face right - NOTE: top of texture continues to top face and bottom of texture continues to bottom face 
		//- WITH SAME ORIENTATION -
		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, 1.f, 1.f);
		part1;


		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, -1.f, 1.f);
		part2;


		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, -1.f, -1.f);
		part3;


		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, 1.f, -1.f);

		//face back
		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, 1.f, -1.f);
		part1;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, -1.f, -1.f);
		part2;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, -1.f, -1.f);
		part3;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, 1.f, -1.f);

		//face left

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, 1.f, -1.f);
		part1;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, -1.f, -1.f);
		part2;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, -1.f, 1.f);
		part3;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, 1.f, 1.f);

		//face top
		boxIteratorY--;
		boxIteratorX = boxIteratorX - 3;


		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, 1.f, 1.f);
		part1;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, 1.f, 1.f);
		part2;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, 1.f, -1.f);
		part3;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, 1.f, -1.f);

		//face bottom
		boxIteratorY++;
		boxIteratorY++;
		boxIteratorX--;


		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, -1.f, 1.f);
		part1;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, -1.f, 1.f);
		part2;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(-1.f, -1.f, -1.f);
		part3;

		glTexCoord2f(TextureCoordX, TextureCoordY);
		glVertex3f(1.f, -1.f, -1.f);
		glEnd();
		toggle->toggleDepth();
		//glEnable(GL_DEPTH_TEST);
		toggle->toggleLit();
		//glEnable(GL_LIGHTING);
	}
	glPopMatrix();
	return;
}
void Scene::render() {

	glutWarpPointer(width / 2, height / 2);
	previousMouseX = width / 2;
	previousMouseY = height / 2;




	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(cameraLord.getCamera(cameraIndex)->getPosX(), cameraLord.getCamera(cameraIndex)->getPosY(), cameraLord.getCamera(cameraIndex)->getPosZ(), cameraLord.getCamera(cameraIndex)->getLookX(), cameraLord.getCamera(cameraIndex)->getLookY(), cameraLord.getCamera(cameraIndex)->getLookZ(), cameraLord.getCamera(cameraIndex)->getUpX(), cameraLord.getCamera(cameraIndex)->getUpY(), cameraLord.getCamera(cameraIndex)->getUpZ());

	ArticulatedPlane* floor = prop.getPlane(0);
	ArticulatedPlane* dogeStencil = prop.getPlane(1);
	ArticulatedPlane* doge = prop.getPlane(2);
	ArticulatedPlane* ceiling = prop.getPlane(3);

	// Render geometry/scene here -------------------------------------


	// Clear Color and Depth Buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	skyBox();

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);		//mask-0
	glStencilFunc(GL_ALWAYS, 1, 1);								//func-0
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);					//op-0
	toggle->toggleDepth();
	//glDisable(GL_DEPTH_TEST);									//depth-0
	glEnable(GL_STENCIL_TEST);									//stencil-0

		//draw floor
	glPushMatrix();
	{
		glTranslatef(-1, 0, 1.f);
		//glBindTexture(GL_TEXTURE_2D, dogeTexture);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		dogeStencil->render();
	}
	glPopMatrix();
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);		//mask-0
	toggle->toggleDepth();
	//glEnable(GL_DEPTH_TEST);								//depth-0
	glStencilFunc(GL_EQUAL, 1, 1);							//func-0
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);					//op-0
	glPushMatrix();
	{
		glScalef(1.0f, -1.0f, 1.0f);
		glPushMatrix();
		skyBox(1, -1, 1);
		glPopMatrix();
		//move below floor
		glTranslatef(5, 0.5, -5);
		prop.getSpotlight(0)->renderFake(6.f, 0.f, 0.f);
		prop.getSpotlight(1)->renderFake(-6.f, 0.f, 0.f);
		//flip vertically
		//give rotation
		glPushMatrix();
		{
			glRotatef(rotation, 0, 1, 0);

			//glScalef(0.06, 0.06, 0.06);
			model[1].render();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glDisable(GL_STENCIL_TEST);								//stencil-0

	toggle->toggleLit();
	//glDisable(GL_LIGHTING);									//lighting-0
	toggle->toggleBlend();
	//glEnable(GL_BLEND);										//blend-0
	glColor4f(0.8f, 0.8f, 0.8f, 0.8f);


	glPushMatrix();
	glTranslatef(-1, 0, 1.f);
	glBindTexture(GL_TEXTURE_2D, dogeTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	doge->render();
	glPopMatrix();


	toggle->toggleLit();
	//glEnable(GL_LIGHTING);									//lighting-0
	toggle->toggleBlend();
	//glDisable(GL_BLEND);									//blend-0
	glClear(GL_STENCIL_BUFFER_BIT);

	glPushMatrix();
	{
		glTranslatef(0, 10, 0.f);
		glPushMatrix();
		{
			glRotatef(180, 1, 0, 0);
			glTranslatef(-50, 0, 50.f);
			ceiling->render();
		}
		glPopMatrix();
	}
	glPopMatrix();




	GLfloat lX, lY, lZ;
	lX = cameraLord.getCamera(1)->getPosX();
	lY = cameraLord.getCamera(1)->getPosY();
	lZ = cameraLord.getCamera(1)->getPosZ();
	prop.getLightBall(0)->render(lX, lY, lZ, cameraLord.getCamera(1)->getForward());
	GLfloat Light_Position[] = { lX, lY, lZ, 1 };



	glPushMatrix();
	{
		glTranslatef(-6.f / 2, -10.f / 2, -35.f);
		glPushMatrix();
		{
			glScalef(0.5f, 0.5f, 0.5f);
			model[2].render();
		}
		glPopMatrix();
	}
	glPopMatrix();

	//corridor
	for (int i = 0; i < 4; i++)
	{
		glPushMatrix();
		{
			glRotatef(90 * i, 0, 0, 1);
			glPushMatrix();
			{
				glTranslatef(-10.f / 2, -10.f / 2, -30.f);
				//statuette(0.f, 0.f, 5.f);
				glBindTexture(GL_TEXTURE_2D, dogeTexture);
				glTexParameteri(GL_TEXTURE_2D, 8, GL_REPEAT);
				glTexParameteri(GL_TEXTURE_2D, 8, GL_REPEAT);
				floor->render();
			}
			glPopMatrix();
		}
		glPopMatrix();
	}









	GLfloat floorVerts[] =
	{
		-10.f,	2.f,	 -10.f,	//top left
		-10.f,	2.f,	 0.f,	// bottom left
		0.f,	2.f,	 0.f,	//bottom right
		0.f,	2.f,	 -10.f	// top right
	};
	//Light_Position

	//for (int i = 0; i < 4; i++) {
	//	Light_Position[i] *= -1;
	//}


	shadowMan.generateShadowMatrix(shadowMatrix, Light_Position, floorVerts);

	glDisable(GL_TEXTURE_2D);
	//floor
	glPushMatrix();
	{
		glTranslatef(-5, 2, 5);
		glBegin(GL_QUADS);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(10.f, 0.f, -10.f);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(10.f, 0.f, 0.f);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glNormal3f(0.f, 1.f, 0.f);
		glVertex3f(0.f, 0.f, -10.f);
		glEnd();
	}
	glPopMatrix();



	//glDisable(GL_LIGHTING);										//lighting-1
	toggle->toggleLit();

	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);		//mask-1
	glStencilFunc(GL_ALWAYS, 1, 1);								//func-1
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);					//op-1
	glEnable(GL_STENCIL_TEST);									//stencil-1
	//draw stencil
	glPushMatrix();
	{
		glTranslatef(-5, 2, 5);
		glBegin(GL_QUADS);
		glVertex3f(10.f, 0.f, -10.f);
		glVertex3f(10.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, 0.f);
		glVertex3f(0.f, 0.f, -10.f);
		glEnd();
	}
	glPopMatrix();

	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);			//mask-1
	glStencilFunc(GL_EQUAL, 1, 1);								//func-1
	glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);						//op-1


	glPushMatrix();
	{
		//glDisable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);										//blend-1
		//glEnable(GL_CULL_FACE);									//cull-0
		//glCullFace(GL_BACK);
		glColor4f(0.1f, 0.1f, 0.1f, 0.2f); // Shadow's colour
		toggle->toggleDepth();
		//glDisable(GL_DEPTH_TEST);									//depth-1
		glPushMatrix();
		{

			glTranslatef(0, 0.01f, 0);
			glMultMatrixf((GLfloat *)shadowMatrix);
			//translate to floor and draw shadow, remember to match any transforms on thessssssssa wwWWw
			glTranslatef(0, 2, 0);
			//glRotatef(rotation, 0.f, 1.f, 0.f);
			glScalef(0.2f, 0.2f, 0.2f);
			model[0].render();
			glColor4f(1.0f, 1.0f, 1.0f, 1.f);
		}
		toggle->toggleDepth();
		//glEnable(GL_DEPTH_TEST);									//depth-1
		glPopMatrix();
		//glDisable(GL_CULL_FACE);									//cull-0
		glDisable(GL_BLEND);										//blend-1


		glDisable(GL_STENCIL_TEST);									//stencil-1
		glEnable(GL_TEXTURE_2D);
		toggle->toggleLit();
		//glEnable(GL_LIGHTING);										//lighting-1


		glColor3f(1.0f, 1.0f, 1.0f); // S

		glPushMatrix();
		{
			glTranslatef(0, 2, 0);
			//glRotatef(rotation, 0.f, 1.f, 0.f);
			glScalef(0.2f, 0.2f, 0.2f);
			model[0].render();
		}
		glPopMatrix();
	}
	glPopMatrix();
	glClear(GL_STENCIL_BUFFER_BIT);
	glPushMatrix();
	{
		glTranslatef(5, 0.5, -5);
		glPushMatrix();
		{
			glRotatef(rotation, 0, 1, 0);

			//glScalef(0.06, 0.06, 0.06);
			model[1].render();
		}
		glPopMatrix();
		//render spotlights after everything so transparent elements can blend with everything
		prop.getSpotlight(0)->render(6.f, 0.f, 0.f);
		prop.getSpotlight(1)->render(-6.f, 0.f, 0.f);
	}
	glPopMatrix();


	// End render geometry --------------------------------------

	// Render text, should be last object rendered.
	renderTextOutput();

	// Swap buffers, after all objects are rendered.
	glutSwapBuffers();
}

// Handles the resize of the window. If the window changes size the perspective matrix requires re-calculation to match new window size.
void Scene::resize(int w, int h)
{
	width = w;
	height = h;
	// Prevent a divide by zero, when window is too short
	// (you cant make a window of zero width).
	if (h == 0)
		h = 1;

	float ratio = (float)w / (float)h;
	fov = 45.0f;
	nearPlane = 0.1f;
	farPlane = 100.0f;

	// Use the Projection Matrix
	glMatrixMode(GL_PROJECTION);

	// Reset Matrix
	glLoadIdentity();

	// Set the viewport to be the entire window
	glViewport(0, 0, w, h);

	// Set the correct perspective.
	gluPerspective(fov, ratio, nearPlane, farPlane);

	// Get Back to the Modelview
	glMatrixMode(GL_MODELVIEW);


}

// Calculates FPS
void Scene::calculateFPS()
{

	frame++;
	time = glutGet(GLUT_ELAPSED_TIME);

	if (time - timebase > 1000) {
		sprintf_s(fps, "FPS: %4.2f", frame*1000.0 / (time - timebase));
		timebase = time;
		frame = 0;
	}
}

// Compiles standard output text including FPS and current mouse position.
void Scene::renderTextOutput()
{
	// Render current mouse position and frames per second.
	sprintf_s(mouseText, "Mouse: %i, %i", input->getMouseX(), input->getMouseY());
	displayText(-1.f, 0.96f, 1.f, 0.f, 0.f, mouseText);
	displayText(-1.f, 0.90f, 1.f, 0.f, 0.f, fps);

	//debugging code
	//sprintf_s(mouseText, "ball position x: %f", cameraLord.getCamera(1)->getPosX());
	//displayText(-1.f, 0.84, 1.f, 0.f, 0.f, mouseText);
	//sprintf_s(mouseText, "ball position x: %f", cameraLord.getCamera(1)->getPosY());
	//displayText(-1.f, 0.78, 1.f, 0.f, 0.f, mouseText);
	//sprintf_s(mouseText, "ball position x: %f", cameraLord.getCamera(1)->getPosZ());
	//displayText(-1.f, 0.72, 1.f, 0.f, 0.f, mouseText);
}

// Renders text to screen. Must be called last in render function (before swap buffers)
void Scene::displayText(float x, float y, float r, float g, float b, char* string) {
	// Get Lenth of string
	int j = strlen(string);

	// Swap to 2D rendering
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -1.0, 1.0, 5, 100);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	// Orthographic lookAt (along the z-axis).
	gluLookAt(0.0f, 0.0f, 10.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f);

	// Set text colour and position.
	glColor3f(r, g, b);
	glRasterPos2f(x, y);
	// Render text.
	for (int i = 0; i < j; i++) {
		glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, string[i]);
	}
	// Reset colour to white.
	glColor3f(1.f, 1.f, 1.f);

	// Swap back to 3D rendering.
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(fov, ((float)width / (float)height), nearPlane, farPlane);
	glMatrixMode(GL_MODELVIEW);
}
