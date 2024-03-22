#pragma once
#ifndef graphics_Draw_Special_Special_h_
#define graphics_Draw_Special_Special_h_
#include "GMath.h"
namespace specialLib
{
	// Blit bufferFrom on bufferOn where blitPosition is a point on bufferOn where putting top left of the bufferFrom. if !byCenter, else: into blitPosition of bufferOn goes center of bufferFrom.
	template<typename buf, typename pointType>
	void blitOn(buf& bufferOn, buf& bufferFrom, gMathLib::Vector2D<pointType> blitPosition, bool byCenter = false)
	{
		using vec = gMathLib::Vector2D<int>;
		using rec = gMathLib::Rectangle<int>;
		rec first  = rec(0, 0, bufferOn.getWidth(), bufferOn.getHeight());
		rec second = rec(blitPosition.x_, blitPosition.y_, bufferFrom.getWidth(), bufferFrom.getHeight());
		if (byCenter)
		{
			second.x_ -= bufferFrom.getWidth()	/	2;
			second.y_ -= bufferFrom.getHeight()	/	2;
		}

		if (!first.isIntersect(second))
			return;
		rec intersect = second.intersect(first);
		int yEnd = intersect.height_ + intersect.y_;
		int xEnd = intersect.width_ + intersect.x_;
		#pragma loop(hint_parallel(8))
		for (int yPos = intersect.y_; yPos < yEnd; yPos++)
		{
			#pragma loop(hint_parallel(8))//may be will help:)))
			for (int xPos = intersect.x_; xPos < xEnd; xPos++)
			{
				bufferOn.blitPix((int)(xPos), (int)(yPos), bufferFrom(xPos - second.x_, yPos - second.y_) );
			}
		}
		return;
		

	}

	template<typename buf, typename color>
	void rotateLeft(buf& rotatedBuf, buf& inputBuf, double angleRadian, color backgroundColor)
	{
		angleRadian = fmod(angleRadian, 2 * PI);
		if (angleRadian < 0) angleRadian += 2 * PI;

		// TODO: chenge that it's a little bit trebling while rotating, i mean if reblit it into the same place with little changing angle.
		float cosAngle = cosf(angleRadian);
		float sinAngle = sinf(angleRadian);
		float oldWidth = inputBuf.getWidth();
		float oldHeight = inputBuf.getHeight();
		float newWidth = fabs(oldHeight * sinAngle) + fabs(oldWidth * cosAngle);
		float newHeight = fabs(oldHeight * cosAngle) + fabs(oldWidth * sinAngle);

		rotatedBuf.init(ceil(newWidth), ceil(newHeight));
		rotatedBuf.fillAll(backgroundColor);
		using vec = gMathLib::Vector2D<float>;

		vec VecUP = vec(0, 1);
		vec VecRIGHT = vec(1, 0);
		vec rotVecUP = gMathLib::rotateLeft(VecUP, angleRadian);
		vec rotVecRIGHT = gMathLib::rotateLeft(VecRIGHT, angleRadian);
		vec toCenter = vec(oldWidth * 0.5f, -oldHeight * 0.5f);

		vec rotateVec = gMathLib::rotateLeft(VecUP, angleRadian +  atanf((float)newWidth / (float)newHeight));
		vec startPos = rotateVec * (sqrtf(newWidth * newWidth + newHeight * newHeight) * 0.5f) + toCenter;

		for (int yPos = 0; yPos < ceil(newHeight); yPos++)
		{
			for (int xPos = 0; xPos < ceil(newWidth); xPos++)
			{
				vec pos = startPos - rotVecUP * yPos + rotVecRIGHT * xPos;
				if (inputBuf.isCorrectPos((int)pos.x_, (int)-pos.y_))
				{
				
				rotatedBuf(xPos, yPos).merge(inputBuf.getPix(pos.x_, -pos.y_));
				}
			}
		}

	}


	template<typename buf>
	void changeResolution(buf& changedBuf, buf& inputBuf, double resizeKoef)
	{
		if (resizeKoef < 0)
		{
			changedBuf.init(0, 0);
			return;
		}
		double reverseResizeKoef = 1. / resizeKoef;
		int oldWidth  = inputBuf.getWidth();
		int oldHeight = inputBuf.getHeight();
		int newWidth  = ceil(oldWidth  * resizeKoef);
		int newHeight = ceil(oldHeight * resizeKoef);
		changedBuf.init(newWidth, newHeight);
		for (int yPosNew = 0; yPosNew < newWidth; yPosNew++)
		{
			float yPosOld = yPosNew * reverseResizeKoef;
			for (int xPosNew = 0; xPosNew < newWidth; xPosNew++)
			{
				float xPosOld = xPosNew * reverseResizeKoef;
				changedBuf(xPosNew, yPosNew) = inputBuf.getPix(xPosOld, yPosOld);
			}
		}
	}

}

#endif // !graphics_Draw_Special_Special_h_
