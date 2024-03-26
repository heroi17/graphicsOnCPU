#pragma once
#ifndef _SAVE_MODULE_SAVE_BUFFER_H_
#define _SAVE_MODULE_SAVE_BUFFER_H_
#include "../linker.h"
#include "libbmp.h"
namespace sBufLib
{
	template <typename buf>
	void save(buf& buffer, const std::string& name)
	{
		int width = buffer.getWidth();
		int height = buffer.getHeight();
		BmpImg img(width, height);

		for (size_t x = 0, y; x < width; x++)
		{
			for (y = 0; y < height; y++)
			{
				auto pix = buffer(x, y);
				img.set_pixel(x, y, pix.getRed(), pix.getGreen(), pix.getBlue());
			}
		}
		img.write(name);
	}
}
#endif // !_SAVE_MODULE_SAVE_BUFFER_H_
