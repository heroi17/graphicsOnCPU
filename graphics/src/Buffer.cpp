#pragma once
#include "../include/Buffer.h"
using namespace bufferLib;

template<class color>
inline bool Buffer2D<color>::_isCorrectPos(int xPos, int yPos) const
{
	if ((0 <= xPos && xPos < this->width_) &&
		(0 <= yPos && yPos < this->height_))
		return true;
	return false;
}

template<class color>
inline int Buffer2D<color>::_cordToInt(int xPos, int yPos) const
{
	int index = yPos * this->width_ + xPos;
	return index;
}

template<class color>
inline bool Buffer2D<color>::isCorrectPos(int xPos, int yPos) const
{
	if ((0 <= xPos && xPos < this->width_) &&
		(0 <= yPos && yPos < this->height_))
		return true;
	return false;
}

template<class color>
void Buffer2D<color>::setPix(int xPos, int yPos, color setColor)
{
	if (!_isCorrectPos(xPos, yPos)) return void();
	int index = _cordToInt(xPos, yPos);
	buffer_[index] = setColor;
}

template<class color>
void Buffer2D<color>::blitPix(int xPos, int yPos, color putColor)
{
	if (!_isCorrectPos(xPos, yPos)) return void();
	int index = _cordToInt(xPos, yPos);
	buffer_[index].merge(putColor);
}

template<class color>
inline void Buffer2D<color>::blitPix(float xPos, float yPos, color putColor)
{
	//TODO: change it like: make rgba8 merge with our putColor and then put it back.
	// But now we have this:
	this->setPix((int)xPos, (int)yPos, putColor);
}
template<>
void Buffer2D<colorLib::RGBA8>::blitPix(float xPos, float yPos, colorLib::RGBA8 putColor)
{
	// Let 0, 0 it's the center of the pixel buffer_(0, 0).
	int xPosInt = (int)(xPos);
	float xPart = xPos - xPosInt;
	int yPosInt = (int)(yPos);
	float yPart = yPos - yPosInt;
	// Mull color by S of (square overlap the pixels).
	colorLib::RGBA8 helper;
	helper = putColor.mulAlpha((1.f - xPart) * (1.f - yPart));
	(*this)(xPosInt, yPosInt).merge(helper);
	helper = putColor.mulAlpha((xPart) * (1.f - yPart));
	(*this)(xPosInt + 1.f, yPosInt).merge(helper);
	helper = putColor.mulAlpha((1 - xPart) * (yPart));
	(*this)(xPosInt, yPosInt + 1.f).merge(helper);
	helper = putColor.mulAlpha((xPart) * (yPart));
	(*this)(xPosInt + 1.f, yPosInt + 1.f).merge(helper);
	// There are sum of area = 1.
}
template<class color>
color Buffer2D<color>::getPix(int xPos, int yPos) const
{
	if (!_isCorrectPos(xPos, yPos)) return ConstOutOfRangePixel_;
	int index = _cordToInt(xPos, yPos);
	return buffer_[index];
}

template<class color>
inline color Buffer2D<color>::getPix(float xPos, float yPos) const
{
	int xPosInt = floorf(xPos);
	float xPart = xPos - xPosInt;
	int yPosInt = floorf(yPos);
	float yPart = yPos - yPosInt;
	// Mull color by S of (square overlap the pixels).
	color answer;
	float koef11 = ((1.f - xPart) * (1.f - yPart));
	float koef12 = ((xPart) * (1.f - yPart));
	float koef21 = ((1 - xPart) * (yPart));
	float koef22 = ((xPart) * (yPart));
	answer = answer + getPix(xPosInt, yPosInt) * koef11;
	answer = answer + getPix(xPosInt + 1, yPosInt) * koef12;
	answer = answer + getPix(xPosInt, yPosInt + 1) * koef21;
	answer = answer + getPix(xPosInt + 1, yPosInt + 1) * koef22;
	return answer;
}

template<class color>
color& Buffer2D<color>::operator()(int xPos, int yPos)
{
	if (!_isCorrectPos(xPos, yPos)) return outOfRangePixel_;
	int index = _cordToInt(xPos, yPos);
	return buffer_[index];
}

template<class color>
void Buffer2D<color>::fillSegment(int yLine, int xStart, int xEnd, color fillColor)
{
	if (!_isCorrectPos(xStart, yLine)) return void();
	if (!_isCorrectPos(xEnd, yLine)) return void();
	auto startIndex = buffer_.begin() + _cordToInt(xStart, yLine);
	auto endIndex = buffer_.begin() + _cordToInt(xEnd, yLine);
	std::fill(startIndex, endIndex, fillColor);

}

template<class color>
inline void Buffer2D<color>::blitSegment(int yLine, int xStart, int xEnd, color fillColor)
{
	xStart = xStart < 0 ? 0 : xStart;
	xEnd = xEnd >= width_ ? width_ - 1 : xEnd;
	if (!_isCorrectPos(xStart, yLine)) return void();
	if (!_isCorrectPos(xEnd, yLine)) return void();
	auto iteratorIndex = buffer_.begin() + _cordToInt(xStart, yLine);
	auto endIndex = buffer_.begin() + _cordToInt(xEnd, yLine);
	for (; iteratorIndex <= endIndex; iteratorIndex++)
	{
		iteratorIndex->merge(fillColor);
	}
}

template<class color>
void Buffer2D<color>::fillAll(color fillColor)
{
	std::fill(buffer_.begin(), buffer_.end(), fillColor);
}

template<class color>
inline void Buffer2D<color>::blitAll(color fillColor)
{
	for (auto startIndex = buffer_.begin(), endIndex = buffer_.end(); startIndex < endIndex; startIndex++)
		startIndex->merge(fillColor);
}

template<class color>
inline void Buffer2D<color>::print()
{
	for (size_t xPos = 0; xPos < width_; xPos++)
	{
		for (size_t yPos = 0; yPos < height_; yPos++)
		{
			int index = this->_cordToInt(xPos, yPos);
			buffer_[index].print();
		}
		printf("\n");
	}
}

template class Buffer2D<colorLib::RGBA8>;