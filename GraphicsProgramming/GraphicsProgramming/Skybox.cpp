#include "Skybox.h"


#define TextureCoordX (boxIteratorX * boxSideTexSize - boxSideTexSize) / boxTexSize
#define TextureCoordY (boxIteratorY * boxSideTexSize - boxSideTexSize) / boxTexSize
#define part1 boxIteratorY++
#define part2 boxIteratorX++
#define part3 boxIteratorY--

void worldSkyBox::skyBoxRun(int x, int y, int z, Toggle* &toggle, CameraLord &cameraLord, int &cameraIndex, float &rotation) //x, y, and z are position scalars
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

worldSkyBox::worldSkyBox()
{
	boxTexSize = 1024; 
	boxSideTexSize = 256;

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
}

worldSkyBox::~worldSkyBox()
{
}

