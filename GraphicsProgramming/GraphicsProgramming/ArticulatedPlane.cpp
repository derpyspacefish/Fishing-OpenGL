#include "ArticulatedPlane.h"
//Articulated Plane by Aristophanes Yates
//Original solution, donut steel!


ArticulatedPlane::ArticulatedPlane(int segments, int width, int length, float texStartX, float texStartY, float texEndX, float texEndY)
{
	float offset = 1.f / segments;// 1/segments
	float offsetX = 1.f / width;// 1/width
	float offsetY = 1.f / length;// 1/length

	float texDeltaX = texEndX - texStartX; //difference in specified texture X positions
	float texDeltaY = texEndY - texStartY; //difference in specified texture Y positions

	for (int quadRow = 0.f; quadRow < length * segments; quadRow++)
	{
		for (int quadColumn = 0.f; quadColumn < width * segments; quadColumn++)
		{
			//top-left vertex
			texXY.push_back(texStartX + (offsetX * quadColumn) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow + offsetY) * offset * texDeltaY);

			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow + offset));


			//bottom-left vertex
			texXY.push_back(texStartX + (offsetX * quadColumn) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow) * offset * texDeltaY);

			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow));


			//bottom-right vertex
			texXY.push_back(texStartX + (offsetX * quadColumn + offsetX) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow) * offset * texDeltaY);

			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn + offset);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow));


			//top-right vertex
			texXY.push_back(texStartX + (offsetX * quadColumn + offsetX) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow + offsetY) * offset * texDeltaY);


			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn + offset);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow + offset));
		}
	}
}

ArticulatedPlane::ArticulatedPlane(vector<float> holeyCoordinates, int segments, int width, int length, float texStartX, float texStartY, float texEndX, float texEndY)
{
	//splitting holeyCoordinates to make it easier to deal with.
	vector<float> holeyCoordinatesXStarts;
	vector<float> holeyCoordinatesYStarts;
	vector<float> holeyCoordinatesXEnds;
	vector<float> holeyCoordinatesYEnds;
	for (int i = 0; i < (holeyCoordinates.size()) / 4; i++)
	{
		holeyCoordinatesXStarts.push_back(holeyCoordinates.at(i * 4)); //i*4 refers to each x starting position. 0, 4, 8...
		holeyCoordinatesYStarts.push_back(holeyCoordinates.at(i * 4 + 1));// the one after each starting x postion
		holeyCoordinatesXEnds.push_back(holeyCoordinates.at(i * 4 + 2));// the one after that
		holeyCoordinatesYEnds.push_back(holeyCoordinates.at(i * 4 + 3));// and the one after that
	}



	float offset = 1.f / segments;// 1/segments
	float offsetX = 1.f / width;// 1/width
	float offsetY = 1.f / length;// 1/length

	float texDeltaX = texEndX - texStartX; //difference in specified texture X positions
	float texDeltaY = texEndY - texStartY; //difference in specified texture Y positions


	for (int quadRow = 0.f; quadRow < length * segments; quadRow++)
	{
		for (int quadColumn = 0.f; quadColumn < width * segments; quadColumn++)
		{
			bool shouldSkip = false;
			for (int holeElement = 0; holeElement < holeyCoordinatesXStarts.size(); holeElement++)// check all specified ranges to see if current quad falls within one of them.
			{
				if (holeElement < holeyCoordinatesXStarts.size())
				{
					if (quadColumn >= holeyCoordinatesXStarts[holeElement] && quadRow >= holeyCoordinatesYStarts[holeElement]) //if not out of bounds leftwise and downwise...
					{
						if (quadColumn < holeyCoordinatesXEnds[holeElement] && quadRow < holeyCoordinatesYEnds[holeElement]) //and if not out of bounds rightwise and upwise...
						{
							shouldSkip = true; // skip to "end" early
							break;
						}
					}
				}
			}
			if (shouldSkip)
			{
				continue;
			}
			//top-left vertex
			texXY.push_back(texStartX + (offsetX * quadColumn) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow + offsetY) * offset * texDeltaY);

			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow + offset));


			//bottom-left vertex
			texXY.push_back(texStartX + (offsetX * quadColumn) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow) * offset * texDeltaY);

			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow));


			//bottom-right vertex
			texXY.push_back(texStartX + (offsetX * quadColumn + offsetX) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow) * offset * texDeltaY);

			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn + offset);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow));


			//top-right vertex
			texXY.push_back(texStartX + (offsetX * quadColumn + offsetX) * offset * texDeltaX);
			texXY.push_back(texEndY - (offsetY * quadRow + offsetY) * offset * texDeltaY);


			normXYZ.push_back(0.f);
			normXYZ.push_back(1.f);
			normXYZ.push_back(0.f);

			vertXYZ.push_back(offset * quadColumn + offset);
			vertXYZ.push_back(0.f);
			vertXYZ.push_back(-(offset * quadRow + offset));

			//"end"
		}
	}
}

ArticulatedPlane::~ArticulatedPlane()
{
}
