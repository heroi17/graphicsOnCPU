#pragma once
#ifndef graphics_Buffer_Color_h_
#define graphics_Buffer_Color_h_
#include <iostream>
#include "GMath.h"
namespace colorLib
{
	// Typedefs for color channel.
	typedef  uint8_t R8;
	typedef  uint8_t G8;
	typedef  uint8_t B8;
	typedef  uint8_t A8;








	class RGBA8
	{
		friend class RGB8;
	protected:
		R8 redChannel_	= 0;
		G8 greenChannel_= 0;
		B8 blueChannel_	= 0;
		A8 alphaChannel_= 0;
	public:

		RGBA8(R8 red = 0, G8 green = 0, B8 blue = 0, A8 alpha = 0);

		RGBA8(const RGBA8& other) = default;
		RGBA8(uint32_t intLike);

		R8 getRed() const { return this->redChannel_; }
		G8 getGreen() const { return this->greenChannel_; }
		B8 getBlue() const { return this->blueChannel_; }
		A8 getAlpha() const { return this->alphaChannel_; }

		void print() const { printf("(%d, %d, %d, %d)", redChannel_, greenChannel_, blueChannel_, alphaChannel_); }

		uint32_t makeInt() const;
		// Write on its color other color.
		void merge(RGBA8 other) noexcept;
		// It's changing alpha channel.

		RGBA8 operator +(const RGBA8& changeAlphaCoef);
		// Multyply alpha channel.
		RGBA8 mulAlpha(const float changeAlphaCoef);
		// chenge all characteristics of pixel
		RGBA8 operator *(const float changeCoef);
	};

}
#endif // !graphics_Buffer_Buffer_h_
