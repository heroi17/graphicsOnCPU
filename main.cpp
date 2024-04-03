// graphics.cpp: определяет точку входа для приложения.
//

#include "graphics/graphics.h"
#include "GraphPainter/graph.h"
#include "SaveModule/saveModule.h"
#include <iostream>
#include <cmath>
#include <thread>
#include <filesystem>
#if defined (_WIN32)
	#define _ON_WINDOWS_
	#include <windows.h>
#endif
inline bool ends_with(std::string const& value, std::string const& ending)
{
	if (ending.size() > value.size()) return false;
	return std::equal(ending.rbegin(), ending.rend(), value.rbegin());
}

using recursive_directory_iterator = std::filesystem::recursive_directory_iterator;

template <typename color>
int output(bufferLib::Buffer2D<color>& buf)
{
#ifdef _ON_WINDOWS_
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

#endif // ON_WINDOWS

	return 0;
}

int test1()
{
#ifdef _ON_WINDOWS_
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
#endif // ON_WINDOWS
	return 0;
}

int test2()
{
	//test1();
	using  S = graphDrawLib::settings;
	GraphObjectLib::GraphObject myGraph = GraphObjectLib::GraphObject();
	switch (myGraph.loadGraph("GraphExamples/GraphTest5.txt"))
	{
	case (GraphObjectLib::ERROR_GRAPH_FILE::GRAPH_FILE_INVALID_SIMBOLOS):
	{
		std::cout << "invalid data";
		return 0;
	}
	case (GraphObjectLib::ERROR_GRAPH_FILE::GRAPH_FILE_NO_EXIST):
	{
		std::cout << "File No Exist";
		return 0;
	}
	}
	auto settings = graphDrawLib::GraphDrawSettings<colorLib::RGBA8>(S::NO_DRAW_NUMIRATION);
	auto myBuf = bufferLib::Buffer2D<colorLib::RGBA8>(500, 500);
	auto myBufBig = bufferLib::Buffer2D<colorLib::RGBA8>(1, 1);
	while (true)
	{
		{
		graphToolsLib::GraphSolver solwerGraph;
		solwerGraph.init(std::move(myGraph));
		for (int i = 0; i <	100; i++)
		{
		solwerGraph.solve();
		}
		myGraph = std::move(solwerGraph);//(or we can do this, but compiler do not like it) solwerGraph.get(myGraph);
		} 
		graphDrawLib::drawGraph(myBuf, myGraph, settings);
		specialLib::changeResolution(myBufBig, myBuf, 1);
		output(myBufBig);
	}

	std::cin.get();

	return 0;
}


int main()
{
	using  S = graphDrawLib::settings;
	GraphObjectLib::GraphObject myGraph = GraphObjectLib::GraphObject();


	auto settings = graphDrawLib::GraphDrawSettings<colorLib::RGBA8>(S::NO_DRAW_NUMIRATION);//flags for draw(graph).
	
	
	
	auto myBuf = bufferLib::Buffer2D<colorLib::RGBA8>(250, 250);
	for (const auto& dirEntry : recursive_directory_iterator("GraphExamples/"))
	{
		std::string outfilename = dirEntry.path().string();
		
		if (!ends_with(outfilename, ".txt")) continue;
		GraphObjectLib::ERROR_GRAPH_FILE ans;
		if (GraphObjectLib::ERROR_GRAPH_FILE::GRAPH_FILE_OK != (ans = myGraph.loadGraph(outfilename)))
		{
			std::cout << outfilename << "(problem with graph contains): exceptions(" << ans << ")\n";
			continue;
		}
		myBuf.init(100, 100);
		for (int jjj = 0; jjj < 40;jjj++)
		{
			{
				graphToolsLib::GraphSolver solwerGraph;
				solwerGraph.init(std::move(myGraph));
				solwerGraph.solve();
				myGraph = std::move(solwerGraph);
			}
			graphDrawLib::drawGraph(myBuf, myGraph, settings);
			output(myBuf);
		}
		myBuf.init(250, 250);
		graphDrawLib::drawGraph(myBuf, myGraph, settings);
		sBufLib::save(myBuf, outfilename.substr(0, outfilename.size() - 4) + ".bmp");
		std::cout << "\"" << outfilename << "\"is saved." << std::endl;
	}
	std::cin.get();
	return 0;
}

int test()
{

	auto myBuf = bufferLib::Buffer2D<colorLib::RGBA8>(250, 250);
	myBuf.init(250, 250);



	auto myGraph = GraphObjectLib::GraphObject();
	std::string outfilename = "GraphExamples/GraphTest1.txt";

	if (GraphObjectLib::ERROR_GRAPH_FILE ans; GraphObjectLib::ERROR_GRAPH_FILE::GRAPH_FILE_OK != (ans = myGraph.loadGraph(outfilename)))
	{
		std::cout << outfilename << "(problem with graph contains): exceptions(" << ans << ")\n";
		return 0;
	}
		
	graphToolsLib::GraphSolver solwerGraph;

	solwerGraph.init(std::move(myGraph));
	for (int jjj = 0; jjj < 40; jjj++) solwerGraph.solve();
	myGraph = std::move(solwerGraph);



	auto settings = graphDrawLib::GraphDrawSettings<colorLib::RGBA8>(graphDrawLib::settings::NO_DRAW_NUMIRATION);//flags for draw(graph).
	graphDrawLib::drawGraph(myBuf, myGraph, settings);
	sBufLib::save(myBuf, "GraphExamples/bufferExample.bmp");
	std::cout << "\"" << outfilename << "\"is saved." << std::endl;
	return 0;
}