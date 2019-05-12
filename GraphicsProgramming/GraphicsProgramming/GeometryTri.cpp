#include "GeometryTri.h"



GeometryTri::GeometryTri()
{
}


GeometryTri::~GeometryTri()
{
}

void GeometryTri::render()
{
	textureBind();

	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	glVertexPointer(3, GL_FLOAT, 0, &vertXYZ[0]);
	glNormalPointer(GL_FLOAT, 0, &normXYZ[0]);
	glTexCoordPointer(2, GL_FLOAT, 0, &texXY[0]);


	glDrawArrays(GL_TRIANGLES, 0, vertXYZ.size() / 3);

	//dereferencing method of choice
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
}
