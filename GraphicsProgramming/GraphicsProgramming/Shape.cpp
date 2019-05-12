#include "shape.h"


extern float verts[] = {	
	//front
							-1.0, 1.0, 1.0,			// Vertex #0
							-1.0, -1.0, 1.0,		// Vertex #1
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  1.0, 1.0,			// Vertex #3
	//right
							1.0,  1.0, 1.0,			// Vertex #4
							1.0,  -1.0, 1.0,		// Vertex #5
							1.0,  -1.0, -1.0,		// Vertex #6
							1.0,  1.0, -1.0,		// Vertex #7
	//back
							1.0, 1.0, -1.0,			// Vertex #8
							1.0, -1.0, -1.0,		// Vertex #9
							-1.0,  -1.0, -1.0,		// Vertex #10
							-1.0,  1.0, -1.0,		// Vertex #11
	//left
							-1.0,  1.0, -1.0,		// Vertex #12
							-1.0,  -1.0, -1.0,		// Vertex #13
							-1.0,  -1.0, 1.0,		// Vertex #14
							-1.0,  1.0, 1.0,		// Vertex #15
	//top
							-1.0, 1.0, 1.0,			// Vertex #0
							1.0,  1.0, 1.0,			// Vertex #4
							1.0, 1.0, -1.0,			// Vertex #8
							-1.0,  1.0, -1.0,		// Vertex #12
	//bottom
							1.0,  -1.0, 1.0,		// Vertex #2
							1.0,  -1.0, -1.0,		// Vertex #6
							-1.0,  -1.0, -1.0,		// Vertex #10
							-1.0,  -1.0, 1.0,		// Vertex #14
							};

extern float norms[] = { 
	//front
						0.0, 0.0, 1.0,		//0
						0.0, 0.0, 1.0,		//1
 						0.0, 0.0, 1.0,		//2
						0.0, 0.0, 1.0,		//3
	//right
						1.0, 0.0, 0.0,		//0
						1.0, 0.0, 0.0,		//1
 						1.0, 0.0, 0.0,		//2
						1.0, 0.0, 0.0,		//3
	//back
						0.0, 0.0, -1.0,		//0
						0.0, 0.0, -1.0,		//1
 						0.0, 0.0, -1.0,		//2
						0.0, 0.0, -1.0,		//3
	//left
						-1.0, 0.0, 0.0,		//0
						-1.0, 0.0, 0.0,		//1
 						-1.0, 0.0, 0.0,		//2
						-1.0, 0.0, 0.0,		//3
	//top
						0.0, 1.0, 0.0,		//0
						0.0, 1.0, 0.0,		//1
 						0.0, 1.0, 0.0,		//2
						0.0, 1.0, 0.0,		//3
	//top
						0.0, -1.0, 0.0,		//0
						0.0, -1.0, 0.0,		//1
 						0.0, -1.0, 0.0,		//2
						0.0, -1.0, 0.0,		//3
						};		


extern float texcoords[]= {	
							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
 							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3

							0.0, 0.0, 		//0
							0.0, 1.0, 		//1
							1.0, 1.0, 		//2
							1.0, 0.0, 		//3
							};

extern GLubyte indices[] = { 
							0, 1, 2, 3, //front
							4, 5, 6, 7, //front
							8, 9, 10, 11, //front
							12, 13, 14, 15, //front
							16, 17, 18, 19, //front
							20, 21, 22, 23, //front
							};
void Shape::renderQuadMethod1()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glBegin(GL_QUADS);
	glArrayElement(0);
	glArrayElement(1);
	glArrayElement(2);
	glArrayElement(3);
	glEnd();


	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	

}

void Shape::renderQuadMethod2()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);


	glDrawArrays(GL_QUADS, 0, 4);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

}

void Shape::renderCubeMethod3()
{
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, verts);
	glNormalPointer(GL_FLOAT, 0, norms);
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, indices);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}

void Shape::renderSphere(int segments, int skipFromEndX, int skipFromEndY)
{
	float theta = (2 * 3.1415962) / segments;
	float delta = 3.1415962 / segments;
	float x;
	float y;
	float z;
	glBegin(GL_QUADS);
	for (float latitude = 0; latitude < segments - skipFromEndY; latitude++) //when latitude = 0, the top vertical slice of the sphere will be generated
	{
		for (float longitude = 0; longitude < segments - skipFromEndX; longitude++)
		{
			//beware, below be an essay. Spheres baffled me for way too long.

			/*

			actor's right<-  "actor"  ->actor's left


			vertex
			/
			yaw left <-/-> yaw right
			/
			/
			/
			/
			/
			"hand"




			hand = centre of the sphere

			actor = viewpoint outside of the sphere looking in


			/
			/   is a "stick" that has a length of r or the sphere's radius
			/


			vertexes are always created at the end of the stick





			note that adding to theta's cofactor (AKA longitude) will normally yaw/turn rightward
			from the perspective of the "hand" (AKA clockwise) before doing the next vertical slice;
			this means that when longitude increases from 0 to 1, the next vertical slice will be
			turned in the direction of actor's left, placing the second slice left of the first
			vertical slice.

			this will cause a conflict with the texture; going from the left-most image segment
			to the right as longitude increases, the first vertical slice will use the left-most
			segment, and second slice to the left of it will use the second-left-most segment.

			this has been rectified by using -theta, causing the slices to be created in order from
			actor's left to actor's right (AKA anti-clockwise) as longitude increases; E.G. right
			yaws/turns become left.

			see comments below for "hand" rotations and vertex orientation from actor's point of view

			*/
			//top left - 0 yaws left, 0 pitches downs
			x = cosf(-theta * (longitude))*sinf(delta*(latitude));
			y = cosf(delta*(latitude));
			z = sinf(-theta * (longitude))*sinf(delta*(latitude));
			//	glColor3f(0, 0, 0);
			glNormal3f(x, y, z);
			glTexCoord2f((1.f / segments) * (longitude), (1.f / segments) * (latitude));
			glVertex3f(x, y, z);

			//bottom left - 0 lefts, 1 pitches downs
			x = cosf(-theta * (longitude))*sinf(delta*(latitude + 1.f));
			y = cosf(delta*(latitude + 1.f));
			z = sinf(-theta * (longitude))*sinf(delta*(latitude + 1.f));
			//	glColor3f(1, 0, 0);
			glNormal3f(x, y, z);
			glTexCoord2f((1.f / segments) * (longitude), (1.f / segments) * (latitude + 1.f));
			glVertex3f(x, y, z);

			//bottom right - 1 yaws left, 1 pitches downs
			x = cosf(-theta * (longitude + 1.f))*sinf(delta*(latitude + 1.f));
			y = cosf(delta*(latitude + 1.f));
			z = sinf(-theta * (longitude + 1.f))*sinf(delta*(latitude + 1.f));
			//	glColor3f(0, 1, 0);
			glNormal3f(x, y, z);
			glTexCoord2f((1.f / segments) * (longitude + 1.f), (1.f / segments) * (latitude + 1.f));
			glVertex3f(x, y, z);

			//top right - 1 yaws left, 0 pitches downs
			x = cosf(-theta * (longitude + 1.f))*sinf(delta*(latitude));
			y = cosf(delta*(latitude));
			z = sinf(-theta * (longitude + 1.f))*sinf(delta*(latitude));
			//	glColor3f(0, 0, 1);
			glNormal3f(x, y, z);
			glTexCoord2f((1.f / segments) * (longitude + 1.f), (1.f / segments) * (latitude));
			glVertex3f(x, y, z);


		}
	}
	glEnd();
}


void Shape::renderDisc(int segments, bool useCircleCalculation, int looper)
{
	float theta = 0;
	float r = 0.f;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float u = 0.f;
	float v = 1.f;
	float d = 2.f;
	float scalar = 1.f;

	glBegin(GL_TRIANGLE_FAN);
	glNormal3f(0.f, 0.f, 1.f);
	glTexCoord2f(0.5f, 0.5f);
	glVertex3f(x, y, z);
	for (float i = 0; i <= segments - looper; i++)
	{
		x = cosf(theta);
		y = sinf(theta);
		glNormal3f(0, 0, 1);
		u = (cosf(theta) / d) + 0.5;
		v = (sinf(theta) / d) + 0.5;
		glTexCoord2f(u, v);
		glVertex3f(x, y, z);
		if (i < segments - 1)
		{
			theta += (2.f * 3.14f) / segments;
		}
		else
		{
			theta = 0;
		}
	}
	glEnd();
}



void Shape::renderCylinder(int segments, int looper)
{
	float theta = (2 * 3.1415962) / segments;
	float angle = 0;
	float r = 1.f;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float u = 0.f;
	float v = 0.f;
	float d = 2.f;


	glBegin(GL_QUADS);
	for (float stacks = 0; stacks < segments; stacks++)
	{
		for (float columns = 0; columns < segments - looper; columns++)
		{
			x = r * cosf(-theta * (columns));
			y = r * (stacks + 1) / segments;
			z = r * sinf(-theta * (columns));
			glTexCoord2f((1.f / segments) * (columns), 1 - (1.f / segments) * (stacks + 1));
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);


			x = r * cosf(-theta * (columns));
			y = r * (stacks) / segments;
			z = r * sinf(-theta * (columns));
			glTexCoord2f((1.f / segments) * (columns), 1 - (1.f / segments) * (stacks));
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);


			x = r * cosf(-theta * (columns + 1));
			y = r *(stacks) / segments;
			z = r * sinf(-theta * (columns + 1));
			glTexCoord2f((1.f / segments) * (columns + 1), 1 - (1.f / segments) * (stacks));
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);


			x = r * cosf(-theta * (columns + 1));
			y = r * (stacks + 1) / segments;
			z = r * sinf(-theta * (columns + 1));
			glTexCoord2f((1.f / segments) * (columns + 1), 1 - (1.f / segments) * (stacks + 1));
			glNormal3f(x, y, z);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
}

void Shape::renderCone(int segmentsX, int segmentsY, float initialRadius, float finalRadius)
{
	float theta = (2 * 3.1415962) / segmentsX;
	float deltaRadius = 0.f;//difference between initialRadius and finalRadius
	float biggestRadius = 0;
	if (finalRadius != -1.f)
	{
		deltaRadius = finalRadius - initialRadius;
	}
	else
	{
		deltaRadius = segmentsY;
	}
	if (initialRadius <= finalRadius)
	{
		biggestRadius = finalRadius;
	}
	else
	{
		biggestRadius = initialRadius;
	}
	float angle = 0;
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
	float normalX, normalY, normalZ;//greatest radius 
	normalY = 1.f;
	float taper = 0.1f;


	glBegin(GL_QUADS);
	for (float stacks = 0; stacks < segmentsY; stacks++)
	{
		for (float columns = 0; columns < segmentsX; columns++)
		{
			x = ( (initialRadius + ((stacks + 1) * deltaRadius / segmentsY)) / segmentsX) * ( cosf(-theta * (columns)));
			y =  (stacks + 1) / segmentsY;
			z = ( (initialRadius + ((stacks + 1) * deltaRadius / segmentsY)) / segmentsX) * sinf(-theta * (columns));
			glTexCoord2f((1.f / segmentsX) * (columns), 1 - (1.f / segmentsY) * (stacks + 1));

			normalX = (biggestRadius *  cosf(-theta * (columns)));
			normalZ = (biggestRadius * sinf(-theta * (columns)));
			glNormal3f(normalX, normalY, normalZ);
			glVertex3f(x, y, z);


			x = ( (initialRadius + (stacks * deltaRadius / segmentsY)) / segmentsX) * cosf(-theta * (columns));
			y =  (stacks) / segmentsY;
			z = ( (initialRadius + (stacks * deltaRadius / segmentsY)) / segmentsX) * sinf(-theta * (columns));
			glTexCoord2f((1.f / segmentsX) * (columns), 1 - (1.f / segmentsY) * (stacks));
			glNormal3f(normalX, normalY, normalZ);
			glVertex3f(x, y, z);
			normalX = (biggestRadius *  cosf(-theta * (columns + 1)));
			normalZ = (biggestRadius * sinf(-theta * (columns + 1)));


			x = ( (initialRadius + (stacks * deltaRadius / segmentsY)) / segmentsX) * cosf(-theta * (columns + 1));
			y =  (stacks) / segmentsY;
			z = ( (initialRadius + (stacks * deltaRadius / segmentsY)) / segmentsX) * sinf(-theta * (columns + 1));
			glTexCoord2f((1.f / segmentsX) * (columns + 1), 1 - (1.f / segmentsY) * (stacks));
			glNormal3f(normalX, normalY, normalZ);
			glVertex3f(x, y, z);


			x = ( (initialRadius + ((stacks + 1) * deltaRadius / segmentsY)) / segmentsX) * cosf(-theta * (columns + 1));
			y =  (stacks + 1) / segmentsY;
			z = ( (initialRadius + ((stacks + 1) * deltaRadius / segmentsY)) / segmentsX) * sinf(-theta * (columns + 1));
			glTexCoord2f((1.f / segmentsX) * (columns + 1), 1 - (1.f / segmentsY) * (stacks + 1));
			glNormal3f(normalX, normalY, normalZ);
			glVertex3f(x, y, z);
		}
	}
	glEnd();
}
