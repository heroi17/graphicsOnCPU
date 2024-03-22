#pragma once
#ifndef graphics_Draw_Shapes_Shapes_h_
#define graphics_Draw_Shapes_Shapes_h_
#include "GMath.h"
#define LEN(point2D) sqrt(point2d.x * point2d.x) + (point2d.y * point2d.y)

namespace shapesLib
{



	template <typename buf, typename color, typename pointType>
	void line(buf& buffer, color fillColor, gMathLib::Vector2D<pointType> pStart, gMathLib::Vector2D<pointType> pEnd)
	{
		using vec = gMathLib::Vector2D < float > ;
		vec delta = pEnd - pStart;
		int lenth = delta.getLength();
		delta.normalize();
		vec iterPos = pStart;
        #pragma loop(hint_parallel(8))
		for (int i = 0; i <= lenth; i++)
		{
			buffer.blitPix((float)(iterPos.x_), (float)(iterPos.y_), fillColor);
			iterPos = iterPos + delta;
			
		}
	}

	template <typename buf, typename color, typename pointType>
	void triangle(buf& buffer, gMathLib::Vector2D<pointType> p1, gMathLib::Vector2D<pointType> p2, gMathLib::Vector2D<pointType> p3, color lineColor)
	{
		line(buffer, lineColor, p1, p2);
		line(buffer, lineColor, p2, p3);
		line(buffer, lineColor, p3, p1);
	}

	template <typename buf, typename color, typename pointType>
	void filledTriangle(buf& buffer, gMathLib::Vector2D<pointType> p1, gMathLib::Vector2D<pointType> p2, gMathLib::Vector2D<pointType> p3, color lineColor, color fillColor)
	{
        //sorting
        if (p1.y_ > p2.y_) std::swap(p1, p2);
        if (p2.y_ > p3.y_) std::swap(p2, p3);
        if (p1.y_ > p2.y_) std::swap(p1, p2);

        float slope1 = ((float)(p2.x_ - p1.x_) / (p2.y_ - p1.y_));
        float slope2 = ((float)(p3.x_ - p2.x_) / (p3.y_ - p2.y_));
        float slope3 = ((float)(p3.x_ - p1.x_) / (p3.y_ - p1.y_));

        float x1; float x2;
        if (p1.y_ == p2.y_) {
            if (p2.x_ > p1.x_) {
                x1 = p1.x_;
                x2 = p2.x_;
            }
            else {
                x1 = p2.x_;
                x2 = p1.x_;
                std::swap(slope2, slope3);
            }
            for (int y = p1.y_; y < p3.y_; y++) {
                buffer.blitSegment(y, x1 + 1, x2, fillColor);
                x1 += slope3;
                x2 += slope2;
            }

        }
        else if (p2.y_ == p3.y_) {

            if (p3.x_ > p2.x_) {
                x1 = p1.x_;
                x2 = p1.x_;
                std::swap(slope1, slope3);
            }
            else {
                x1 = p1.x_;
                x2 = p1.x_;
            }
            for (int y = p1.y_; y < p3.y_; y++) {
                buffer.blitSegment(y, x1+1, x2, fillColor);
                x1 += slope3;
                x2 += slope1;
            }

        }
        else {
            if (slope1 >= slope3)
            {
                x1 = p1.x_;
                x2 = p1.x_;
                for (int y = p1.y_; y < p2.y_; y++) {

                    buffer.blitSegment(y, x1 + 1, x2, fillColor);
                    x1 += slope3;
                    x2 += slope1;
                }

                for (int y = p2.y_; y < p3.y_; y++) {
                    buffer.blitSegment(y, x1 + 1, x2, fillColor);
                    x1 += slope3;
                    x2 += slope2;
                }
            }
            else
            {
                x1 = p1.x_;
                x2 = p1.x_;
                for (int y = p1.y_; y < p2.y_; y++) {

                    buffer.blitSegment(y, x2 + 1, x1, fillColor);
                    x1 += slope3;
                    x2 += slope1;
                }

                for (int y = p2.y_; y < p3.y_; y++) {
                    buffer.blitSegment(y, x2 + 1, x1, fillColor);
                    x1 += slope3;
                    x2 += slope2;
                }
            }
        }
		line(buffer, lineColor, p1, p2);
		line(buffer, lineColor, p2, p3);
		line(buffer, lineColor, p3, p1);
	}

    template <typename buf, typename color, typename pointType>
    void circle(buf& buffer, gMathLib::Vector2D<pointType> center, double radius, color lineColor)
    {
        int rad_sq = radius * radius;
        int YStart = (radius < center.y_) ? -radius : -center.y_;
        int YEnd = (buffer.getHeight() - radius > center.y_) ? radius : buffer.getHeight() - center.y_;
        for (float y = YStart; y < YEnd; y++)
        {

            double current_rad = sqrt(rad_sq - y * y);
            buffer.blitPix((float)(center.x_ - current_rad), (float)(y + center.y_), lineColor);
            buffer.blitPix((float)(center.x_ + current_rad), (float)(y + center.y_), lineColor);
        }
        int XStart = (radius < center.x_) ? -radius : -center.x_;
        int XEnd = (buffer.getWidth() - radius > center.x_) ? radius : buffer.getWidth() - center.x_;
        for (float x = XStart; x < XEnd; x++)
        {

            double current_rad = sqrt(rad_sq - x * x);
            buffer.blitPix((float)(x + center.x_), (float)(center.y_ - current_rad), lineColor);
            buffer.blitPix((float)(x + center.x_), (float)(center.y_ + current_rad), lineColor);
        }
    }

    template <typename buf, typename color, typename pointType>
    void filledCircle(buf& buffer, gMathLib::Vector2D<pointType> center, double radius, color lineColor, color fillColor)
    {
        int rad_sq = radius * radius;
        int YStart = (radius < center.y_) ? -radius : -center.y_;
        int YEnd = (buffer.getHeight() - radius > center.y_) ? radius : buffer.getHeight() - center.y_;
        for (float y = YStart; y <= round(YEnd); y++)
        {
            double current_rad = sqrt(rad_sq - y * y);
            buffer.blitSegment(round(y + center.y_), ceil(center.x_ - current_rad), (float)(center.x_ + current_rad), fillColor);
        }
        circle(buffer, center, radius, lineColor);
    }

    template <typename buf, typename color, typename pointType>
    void rectangle(buf& buffer, gMathLib::Vector2D<pointType> topLeft, gMathLib::Vector2D<pointType> widthHeight, color lineColor)
    {
        using vec = gMathLib::Vector2D<pointType>;
        vec topRight    = topLeft + vec(widthHeight.x_, 0);
        vec bottomRight = topLeft + widthHeight;
        vec bottomLeft  = topLeft + vec(0, widthHeight.y_);
        line(buffer, lineColor, topLeft, topRight);
        line(buffer, lineColor, topRight, bottomRight);
        line(buffer, lineColor, bottomRight, bottomLeft);
        line(buffer, lineColor, bottomLeft, topLeft);
    }

    template <typename buf, typename color, typename pointType>
    void filledRectangle(buf& buffer, gMathLib::Vector2D<pointType> topLeft, gMathLib::Vector2D<pointType> widthHeight, color lineColor, color fillColor)
    {
        float XStart = (0 > topLeft.x_) ? 0 : topLeft.x_;
        float XEnd = (buffer.getWidth() < topLeft.x_ + widthHeight.x_) ? buffer.getWidth() : topLeft.x_ + widthHeight.x_;
        float YStart = (0 > topLeft.y_) ? 0 : topLeft.y_;
        float YEnd = (buffer.getHeight() < topLeft.y_ + widthHeight.y_) ? buffer.getHeight() : topLeft.y_ + widthHeight.y_;

        for (size_t y = round(YStart); y < round(YEnd); y++)
        {
            buffer.blitSegment(y, round(XStart), round(XEnd), fillColor);
        }
        rectangle(buffer, topLeft, widthHeight, lineColor);
    }


}

#endif // !graphics_Draw_Shapes_Shapes_h_
