
#pragma once
#ifndef graphics_Draw_Font_Font_h_
#define graphics_Draw_Font_Font_h_

#define MAX_SIMBOLS          256 // This number is standard, do not change it. =256.
#define FONT_HEADER_NAME_LEN 110 // This number is standard, do not change it. =110.

#include "Color.h"
#include "GMath.h"
#include "Buffer.h"

// This namespace allows you to use a font to draw it on an image.BMP.
namespace fontLib
{
/* May be sometimes later.
	/// <summary>
	/// The structure that we placed directly at the beginning of "Font.bmp", at the beginning of the image.
	/// It is located like this: |header bmp| (our header) image data|.
	/// </summary>
	template<typename COLOR_TYPE = colorLib::RGBA8>
	struct FontHeader
	{
		unsigned char name[FONT_HEADER_NAME_LEN] = { '\0' };
		unsigned short width = 0;
		unsigned short height = 0;
		COLOR_TYPE backgroundColor = COLOR_TYPE(6, 6, 6, 0);// standard for none backgroundcolor is 6_6_6_0 
		unsigned char asciiPointer[256] = { '\0' };
		long long checkSum = 0; //TODO: make correct checking .
	};

	enum FontError
	{
		FONT_BAD_FONT_FILE,
		FONT_NO_BUF,
		FONT_NO_INIT,
		FONT_NO_FIND_SYMBOL,
		FONT_OK = 0,
	};

	// This is the structure that we need to initialize. it makes it possible to draw lines.
	template<typename COLOR_TYPE = colorLib::RGBA8>
	struct Font
	{
	private:
		bool isInit_ = false;
		FontError initError_;

		int yStartChars_ = 1;
		int symbolsPerWidth_ = 0;
		bufferLib::Buffer2D<COLOR_TYPE> thisFontBMP_;

		FontHeader fontHeader_ = FontHeader();
	public:



		// Open filename and get the value of this font. Without calling it, Font won't do anything.
		FontError init(const std::string& filename); // we should to load rgb into rjba with a = 0!!

		bool wasInit() { return isInit_; }

		int getWidthChar() { return fontHeader_.width; }

		int getHeightChar() { return fontHeader_.height; }

		template <typename buf>
		FontError blitChar(buf& buffer, unsigned char symbol, const gMathLib::Vector2D<int>& position);

		template <typename buf>
		FontError blitChar(buf& buffer, unsigned char symbol, const gMathLib::Vector2D<int>& position, const gMathLib::Vector2D<int>& size);

		// Get position on the our code style where symbol is simple char from ascii.
		gMathLib::Vector2D<int> getLTPosChar(unsigned char symbol);


		template <typename buf>
		FontError blitText(buf& buffer, const std::string& text, const Font& textFont, const gMathLib::Vector2D<int>& position);
	};

	template<typename COLOR_TYPE = colorLib::RGBA8>
	gMathLib::Vector2D<int> getLTPosChar(unsigned char symbol)
	{
		int numCharOnBMP = (int)fontHeader_.asciiPointer[symbol];
		int xNumChar = numCharOnBMP % symbolsPerWidth_;
		int yNumChar = numCharOnBMP / symbolsPerWidth_;

		return gMathLib::Vector2D<int>(xNumChar * fontHeader_.width, yNumChar * fontHeader_.height + yStartChars_); //interesting! will be coppied our vector2d or not?
	}

	template<typename COLOR_TYPE> template<typename buf>
	FontError Font<COLOR_TYPE>::blitChar(buf& buffer, unsigned char symbol, const gMathLib::Vector2D<int> &position)
	{

		if (!isInit_) return FONT_NO_INIT;
		auto startPos = getLTPosChar(symbol);
		int xStartPix = startPos.x_;
		int yStartPix = startPos.y_;
		for (size_t x = 0; x < fontHeader_.width; x++)
		{
			for (size_t y = 0; y < fontHeader_.height; y++)
			{
				COLOR_TYPE colorPix = this->thisFontBMP_.get_pix(xStartPix + x, yStartPix + y);
				if (colorPix != fontHeader_.backgroundColor)
					buffer.set_pixel(position.x_ + x, position.y_ + y, colorPix);
			}
		}
		return FONT_OK;
	}

	template<typename COLOR_TYPE> template<typename buf>
	FontError Font<COLOR_TYPE>::blitText(buf& buffer, const std::string& text, const Font& textFont, const gMathLib::Vector2D<int>& position)
	{
		if (!textFont.wasInit()) return FONT_NO_INIT;
		auto helpPosition = position;
		auto oneCharWidth = gMathLib::Vector2D<int>(textFont.getWidthChar(), 0);
		for (size_t character = 0; character < text.size(); character++)
		{
			textFont.blitChar(buffer, text[character], helpPosition);
			helpPosition = helpPosition + oneCharWidth;
		}
		return FONT_OK;

	}
	
	template<typename COLOR_TYPE>
	FontError Font<COLOR_TYPE>::init(const std::string& filename)
	{
		BmpError error = thisFontBMP_.read(filename);
		// If thisFontBMP_ is not open, then stop initialization.
		if (error != BMP_OK)
		{
			initError_ = FONT_NO_BUF;
			return initError_;
		}

		yStartChars_ = ceil(thisFontBMP_.get_width() / (float)sizeof(FontHeader));
		// If there is not enough space for our header, then stop initialization.
		if (yStartChars_ > thisFontBMP_.get_height())
		{
			initError_ = FONT_BAD_FONT_FILE;
			return initError_;
		}


		// Just filling in our header.
		memcpy(&fontHeader_, thisFontBMP_.get_data_start(), sizeof(FontHeader));

		// TODO: 1) Add a check for each character: is this enough to be placed in our BMP.
		// Like call the checker function
		// 
		// TODO: 2) Add a check for correct checksum in the end of the fontHeader_.

		isInit_ = true;
		symbolsPerWidth_ = thisFontBMP_.get_width() / fontHeader_.width;
		initError_ = FONT_OK;
		// All positions are correct.
		return initError_;
	}
*/
}

#endif // !graphics_Draw_Font_Font_h_