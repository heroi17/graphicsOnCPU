#pragma once
#ifndef graphics_Buffer_Buffer_h_
#define graphics_Buffer_Buffer_h_
#include <iostream>
#include <vector>
#include <algorithm>
#include "../include/Color.h"
namespace bufferLib
{

	template <class color>
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

		const std::vector<color>& getBuffer() const { return buffer_; }

		// Put on top of the old pixel the new one - putColor.
		void	blitPix(int xPos, int yPos, color putColor);

		// If you want to change a non-specific pixel. This changes a few pixels near the position. It cost a lot bigger to use then with int cords.
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

	};

}

#endif // !graphics_Buffer_Buffer_h_
