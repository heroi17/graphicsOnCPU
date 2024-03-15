// graphics.cpp: определяет точку входа для приложения.
//

#include "graphics/graphics.h"
#include<windows.h>
#include<iostream>
#include <cmath>
#include <thread>
template <typename color>
int output(bufferLib::Buffer2D<color>& buf)
{
	//Get a console handle
	HWND myconsole = GetConsoleWindow();
	//Get a handle to device context
	HDC mydc = GetDC(myconsole);

	for (size_t xPos = 0; xPos < buf.getWidth(); xPos++)
	{
		for (size_t yPos = 0; yPos < buf.getHeight(); yPos++)
		{
			color pix = buf(xPos, yPos);
			SetPixel(mydc, xPos, yPos, RGB(pix.getRed(), pix.getGreen(), pix.getBlue()));
		}
	}
	return 0;
}

int main()
{
	int width = 200;
	int height = 200;
	auto myBuf = bufferLib::Buffer2D<colorLib::RGBA8>(width, height);
	auto myBuf2 = bufferLib::Buffer2D<colorLib::RGBA8>(50, 50);
	auto myBuf3 = bufferLib::Buffer2D<colorLib::RGBA8>(50, 50);
	colorLib::RGBA8 pix1(255, 255, 255, 255);
	colorLib::RGBA8 pix2(0, 0, 0, 0);
	colorLib::RGBA8 pix3(0, 254, 0, 255);
	colorLib::RGBA8 pix4(255, 0, 0, 255);
	colorLib::RGBA8 blue(0, 0, 255, 255);
	myBuf.fillAll(pix1);
	output(myBuf3);
	//myBuf.blitAll(pix2);
	double angle = 0;
	POINT p;
	RECT rect;
	HWND myconsole = GetConsoleWindow();
	HWND hWindowConsole = GetConsoleWindow();
	RECT r;
	GetWindowRect(hWindowConsole, &r); //stores the console's current dimensions
	MoveWindow(hWindowConsole, r.left, r.top, width+35, height+40, TRUE);
	myBuf2.fillAll(colorLib::RGBA8(255, 0, 0, 100));
	drawBuffer2D::filledCircle(myBuf2, gMathLib::Vector2D<int>(25, 25), 24, pix4, pix3);
	drawBuffer2D::filledTriangle(myBuf2, gMathLib::Vector2D<int>(25, 1), gMathLib::Vector2D<int>(10, 10), gMathLib::Vector2D<int>(40, 10), pix4, pix3);
	drawBuffer2D::filledRectangle(myBuf2, gMathLib::Vector2D<int>(20, 10), gMathLib::Vector2D<int>(10, 20), pix4, pix3);
	drawBuffer2D::changeResolution(myBuf3, myBuf2, 3);
	drawBuffer2D::changeResolution(myBuf2, myBuf3, 1.);
	while (true)
	{
		GetPhysicalCursorPos(&p);
		GetWindowRect(myconsole, &rect);
		angle += PI / 32;
		output(myBuf);
		myBuf.fillAll(blue);
		

		gMathLib::Vector2D<float> upVec(0, 1);


		drawBuffer2D::rotateLeft(myBuf3, myBuf2, PI-gMathLib::VectorAngle(upVec, gMathLib::Vector2D<float>(p.x- 35 - rect.left, p.y-55 - rect.top)), colorLib::RGBA8(0, 0, 0, 120));
		drawBuffer2D::blitOn(myBuf, myBuf3, gMathLib::Vector2D<int>(width / 2, height / 2), true);
		std::this_thread::sleep_for(std::chrono::milliseconds(250));
	}
	return 0;
}