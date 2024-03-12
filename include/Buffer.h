#pragma once
#ifndef graphics_Buffer_Buffer_h_
#define graphics_Buffer_Buffer_h_
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Color.h"
namespace bufferLib
{

	template <typename color>
	class Buffer2D
	{
	private:
		std::vector<color> buffer_			;
		color outOfRangePixel_	= color(0, 0, 0, 0)	;
		const color ConstOutOfRangePixel_ = color(0, 0, 0, 0);
		int size_				= 0			;
		int width_				= 0			;
		int height_				= 0			;
		// Returns true if position inside buffer.
		inline bool _isCorrectPos(int xPos, int yPos) const;

		inline int _cordToInt(int xPos, int yPos) const;

	public:	
		// Returns true if position inside buffer.
		bool isCorrectPos(int xPos, int yPos) const;

		Buffer2D(int width, int height)
		{
			if (width < 0) width = 0;
			if (height < 0) height = 0;
			size_ = width * height;
			width_ = width;
			height_ = height;
			buffer_ = std::vector<color>(size_);
		}

		void init(int width, int height)
		{
			if (width < 0) width = 0;
			if (height < 0) height = 0;
			size_ = width * height;
			width_ = width;
			height_ = height;
			buffer_ = std::vector<color>(size_);
		}

		// Simple access to private fields.

		int		getSize		(void)	const	{ return size_; }
		int		getWidth	(void)	const 	{ return width_;	}
		int		getHeight	(void)	const	{ return height_; }

		// Remove old pix and put there the new one - setColor.
		void	setPix(int xPos, int yPos, color setColor);

		// Put on top of the old pixel the new one - putColor.
		void	blitPix(int xPos, int yPos, color putColor);

		// If you want to change a non-specific pixel. This changes a few pixels near the position. It cost a lot bigger to use then with int cords.
		void	blitPix(float xPos, float yPos, color putColor);

		// get pixel, if it's out of range, then it returns an outOfRangePixel_.
		// get pixel, if it's out of range, then it returns an outOfRangePixel_.
		color	getPix(int xPos, int yPos) const;

		color	getPix(float xPos, float yPos) const;
		// Provide you to safe changing pixel. If position out of range, then it returns outOfRangePixel_&.
		color& operator()	(int xPos, int yPos);


		// Reset pixels in segment.
		void	fillSegment(int yLine, int xStart, int xEnd, color fillColor);

		// Reset pixels in segment.
		void	blitSegment(int yLine, int xStart, int xEnd, color fillColor);

		// Reset all pixels.
		void	fillAll(color fillColor);

		void	blitAll(color fillColor);
		
		void print();

		//TODO: rotateLeft by angle.

	};







	// Returns true if position inside buffer.
	template<typename color>
	inline bool Buffer2D<color>::_isCorrectPos(int xPos, int yPos) const
	{
		if ((0 <= xPos && xPos < this->width_) &&
			(0 <= yPos && yPos < this->height_))
			return true;
		return false;
	}

	template<typename color>
	inline int Buffer2D<color>::_cordToInt(int xPos, int yPos) const
	{
		int index = yPos * this->width_ + xPos;
		return index;
	}

	// Returns true if position inside buffer.
	template<typename color>
	inline bool Buffer2D<color>::isCorrectPos(int xPos, int yPos) const
	{
		if ((0 <= xPos && xPos < this->width_) &&
			(0 <= yPos && yPos < this->height_))
			return true;
		return false;
	}

	// Remove old pix and put there the new one - setColor.
	template<typename color>
	void Buffer2D<color>::setPix(int xPos, int yPos, color setColor)
	{
		if (!_isCorrectPos(xPos, yPos)) return void();
		int index = _cordToInt(xPos, yPos);
		buffer_[index] = setColor;
	}

	// Put on top of the old pixel the new one - putColor.
	template<typename color>
	void Buffer2D<color>::blitPix(int xPos, int yPos, color putColor)
	{
		if (!_isCorrectPos(xPos, yPos)) return void();
		int index = _cordToInt(xPos, yPos);
		buffer_[index].merge(putColor);
	}

	// If you want to change a non-specific pixel. This changes a few pixels near the position. It cost a lot bigger to use then with int cords.
	template<typename color>
	void Buffer2D<color>::blitPix(float xPos, float yPos, color putColor)
	{
		//TODO: change it like: make rgba8 merge with our putColor and then put it back.
		// But now we have this:
		this->setPix((int)xPos, (int)yPos, putColor);
	}

	// get pixel, if it's out of range, then it returns an outOfRangePixel_.
	template<typename color>
	color Buffer2D<color>::getPix(int xPos, int yPos) const
	{
		if (!_isCorrectPos(xPos, yPos)) return ConstOutOfRangePixel_;
		int index = _cordToInt(xPos, yPos);
		return buffer_[index];
	}

	template<typename color>
	inline color Buffer2D<color>::getPix(float xPos, float yPos) const
	{
		int xPosInt = floorf(xPos); // it was a bug here: i use (int)(xPos) and if xPos < 0 then (int)xPos working like ceil(xPos). becouse of it program works not so good.
		float xPart = xPos - xPosInt;
		int yPosInt = floorf(yPos);
		float yPart = yPos - yPosInt;
		// Mull color by S of (square overlap the pixels).
		color answer;
		float koef11 = ((1.f - xPart) * (1.f - yPart));//wrong formula
		float koef12 = ((xPart) * (1.f - yPart));
		float koef21 = ((1 - xPart) * (yPart));
		float koef22 = ((xPart) * (yPart));
		//TODO: here we can lost some pixel by deviding them. so we should found som variant.
		// we can made not just the RGBA8 but RGBAtemlate maybe for more big color palite or for using float for more correct adding colors.
		answer = answer + getPix(xPosInt,			yPosInt) * koef11;
		answer = answer + getPix(xPosInt + 1,	yPosInt) * koef12;
		answer = answer + getPix(xPosInt,			yPosInt + 1) * koef21;
		answer = answer + getPix(xPosInt + 1,	yPosInt + 1) * koef22;
		return answer;
	}

	// Provide you to safe changing pixel. If position out of range, then it returns outOfRangePixel_&.
	template<typename color>
	color& Buffer2D<color>::operator()(int xPos, int yPos)
	{
		if (!_isCorrectPos(xPos, yPos)) return outOfRangePixel_;
		int index = _cordToInt(xPos, yPos);
		return buffer_[index];
	}

	template<typename color>
	void Buffer2D<color>::fillSegment(int yLine, int xStart, int xEnd, color fillColor)
	{
		if (!_isCorrectPos(xStart, yLine)) return void();
		if (!_isCorrectPos(xEnd, yLine)) return void();
		auto startIndex = buffer_.begin() + _cordToInt(xStart, yLine);
		auto endIndex = buffer_.begin() + _cordToInt(xEnd, yLine);
		std::fill(startIndex, endIndex, fillColor);

	}

	template<typename color>
	inline void Buffer2D<color>::blitSegment(int yLine, int xStart, int xEnd, color fillColor)
	{
		xStart = xStart < 0 ? 0 : xStart;
		xEnd = xEnd >= width_ ? width_ -1: xEnd;
		if (!_isCorrectPos(xStart, yLine)) return void();
		if (!_isCorrectPos(xEnd, yLine)) return void();
		auto iteratorIndex = buffer_.begin() + _cordToInt(xStart, yLine);
		auto endIndex = buffer_.begin() + _cordToInt(xEnd, yLine);
		for (; iteratorIndex <= endIndex ; iteratorIndex++)
		{
			iteratorIndex->merge(fillColor);
		}
	}

	template<typename color>
	void Buffer2D<color>::fillAll(color fillColor)
	{
		std::fill(buffer_.begin(), buffer_.end(), fillColor);
	}

	template<typename color>
	inline void Buffer2D<color>::blitAll(color fillColor)
	{
		for (auto startIndex = buffer_.begin(), endIndex = buffer_.end(); startIndex < endIndex; startIndex++)
			startIndex->merge(fillColor);
	}

	template<typename color>
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



}

#endif // !graphics_Buffer_Buffer_h_
