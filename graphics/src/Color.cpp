#include "../include/Color.h"
#include <vector>

namespace colorLib
{
	typedef unsigned int uint;
	RGBA8::RGBA8(R8 red, G8 green, B8 blue, A8 alpha)
	{
		redChannel_ = red;
		greenChannel_ = green;
		blueChannel_ = blue;
		alphaChannel_ = alpha;
	}

	RGBA8::RGBA8(uint32_t intLike)
	{
		memcpy((void*)this, (void*)&intLike, sizeof(RGBA8));
	}

	uint32_t RGBA8::makeInt() const
	{
		uint32_t returns;
		memcpy((void*)&returns, (void*)this, sizeof(RGBA8));
		return returns;
	}

	void RGBA8::merge(RGBA8 other) noexcept
	{
		//https://en.wikipedia.org/wiki/Alpha_compositing

		float alpha1 = this->alphaChannel_ / 255.f;
		float red1 = this->redChannel_ / 255.f;
		float green1 = this->greenChannel_ / 255.f;
		float blue1 = this->blueChannel_ / 255.f;

		float alpha2 = other.alphaChannel_ / 255.f;
		float red2 = other.redChannel_ / 255.f;
		float green2 = other.greenChannel_ / 255.f;
		float blue2 = other.blueChannel_ / 255.f;

		float newAlpha = alpha1 * (1.f - alpha2) + alpha2;
		float newRed = (red2 * alpha2 + red1 * (1.f - alpha2));
		float newGreen = (green2 * alpha2 + green1 * (1.f - alpha2));
		float newBlue = (blue2 * alpha2 + blue1 * (1.f - alpha2));

		this->alphaChannel_ =	(A8)(newAlpha * 255.f);
		this->redChannel_ =		(R8)(newRed * 255.f);
		this->greenChannel_ =	(G8)(newGreen * 255.f);
		this->blueChannel_ =	(B8)(newBlue * 255.f);

	}

	RGBA8 RGBA8::mulAlpha(const float changeAlphaCoef)
	{
		if (changeAlphaCoef < 0) return RGBA8();
		RGBA8 helper = RGBA8(*this);
		uint32_t newAlphaChannel = helper.alphaChannel_ * changeAlphaCoef;
		helper.alphaChannel_ = (A8)CUT_UP(newAlphaChannel, 255);
		return helper;
	}

	RGBA8 RGBA8::operator+(const RGBA8& other)
	{
		RGBA8 newColor;
		// TODO: add vectorization here.
		uint newRedChannel		= (uint)redChannel_ + (uint)other.redChannel_;
		newColor.redChannel_		= (R8)CUT_UP(newRedChannel,		255);

		uint newGreenChannel	= (uint)greenChannel_ + (uint)other.greenChannel_;
		newColor.greenChannel_		= (G8)CUT_UP(newGreenChannel,	255);

		uint newBlueChannel		= (uint)blueChannel_ + (uint)other.blueChannel_;
		newColor.blueChannel_		= (B8)CUT_UP(newBlueChannel,	255);

		uint newAlphaChannel	= (uint)alphaChannel_ + (uint)other.alphaChannel_;
		newColor.alphaChannel_		= (A8)CUT_UP(newAlphaChannel,	255);
		return newColor;
	}
	RGBA8 RGBA8::operator*(const float changeCoef)
	{
		if (changeCoef < 0) return RGBA8();
		// TODO: add vectorization here.
		RGBA8 helper = RGBA8(0, 0, 0, 0);
		uint newRedChannel = ((uint)redChannel_) * changeCoef;
		helper.redChannel_ = (A8)CUT_UP(newRedChannel, 255);

		uint newGreenChannel = ((uint)greenChannel_) * changeCoef;
		helper.greenChannel_ = (A8)CUT_UP(newGreenChannel, 255);

		uint newBlueChannel = ((uint)blueChannel_) * changeCoef;
		helper.blueChannel_ = (A8)CUT_UP(newBlueChannel, 255);

		uint newAlphaChannel = ((uint)alphaChannel_) * changeCoef;
		helper.alphaChannel_ = (A8)CUT_UP(newAlphaChannel, 255);
		return helper;
	}
}