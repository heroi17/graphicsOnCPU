//
// 				<This code maded by Markov Mikhail 21.03.2024>
// 
//		This module gave you some settings structure for drawing 
//	graph using GraphObject from GraphObject.h. Draw function use buffer2D
//  from Buffer.h. Actually this code do not save picture, it's just blit
//  graph on buffer.
// 
///////////////////////////////////////////////////////////////////////////////




#pragma once
#ifndef _GRAPHPAINTER_INCLUDE_GRAPHDRAW_H_
#define _GRAPHPAINTER_INCLUDE_GRAPHDRAW_H_
#include "GraphObject.h"
#include <string> // here i use std::to_string
namespace graphDrawLib
{
	//          _														  _
	//----------|----------------------| SOME FLAGS |---------------------|---------------
	//          V														  V
	enum class settings {
		DRAW_NO_FLAGS			= 0,
		NO_DRAW_BACKGROUND		= 1,
		NO_DRAW_NUMIRATION		= 1 << 1,
		NO_DRAW_LINKS			= 1 << 2,
		NO_DRAW_NODES			= 1 << 3,
		NO_DINAMICK_SETTINGS	= 1 << 4 // counting node Size by dependencing how node we have and what size is it .
	};
	settings operator |(settings a, settings b) {
		return static_cast<settings>(static_cast<unsigned>(a) | static_cast<unsigned>(b));
	}
	settings operator &(settings a, settings b) {
		return static_cast<settings>(static_cast<unsigned>(a) & static_cast<unsigned>(b));
	}
	//
	//-------------------------------| END FLAGS |-----------------------------------------
	//
	

	//			_														   _
	//----------|---------------| SETTINGS FOR DRAWING GRAPH|--------------|---------------
	//			V														   V
	// you can use it like offset or size responded by your buffer size.
	struct SizePartType {
		bool ByPart;
		float value;
		float partValue;

		SizePartType(bool ByPart = true, float value = 20., float partValue = 0.15) : ByPart(ByPart), value(value), partValue(partValue) {}

		float getPartValue(float dimensions) const
		{
			if (ByPart) return partValue;
			if (dimensions == 0) return 0;
			return value / dimensions;
		}
		float getValue(float dimensions) const
		{
			if (ByPart) return partValue * dimensions;
			return value;
		}
	};

	template <typename color>
	struct ShapeColorSettings
	{
		color outlineColor = color(255, 0, 0, 255);
		color interiorColor = color(0, 0, 255, 128);
		float outlineWidth = 1;
		SizePartType outlineSize;
	};

	template <typename color>
	struct NodeDrawSettings
	{
		ShapeColorSettings<color> colorSettings;
		SizePartType nodeDiameter = SizePartType(true, 0, 0.01);

		template <typename buf, typename pointType>
		void draw(buf& buffer, gMathLib::Vector2D<pointType> center)
		{
			//TODO: add here checkink for width/heifht and so on.
			double nodeRadius = nodeDiameter.value;
			drawBuffer2D::filledCircle(buffer, center, nodeDiameter.getValue(buffer.getWidth()), this->colorSettings.outlineColor, this->colorSettings.interiorColor);
		}
		
	};

	template <typename color>
	struct LineDrawSettings
	{
		ShapeColorSettings<color> colorSettings;
		SizePartType lineWidth; 

		template <typename buf, typename pointType>
		void draw(buf& buffer, gMathLib::Vector2D<pointType> pStart, gMathLib::Vector2D<pointType> pEnd)
		{
			//TODO: add here checking for width line and add to drow outline color of line!.
			drawBuffer2D::line(buffer, colorSettings.interiorColor, pStart, pEnd);
		}

	};

	template <typename color>
	struct FontDrawSettings
	{
		ShapeColorSettings<color> colorSettings;
		SizePartType fontHeight = SizePartType(true, 0, 0.05);
		bool drawByCenter = true;

		template <typename buf, typename pointType>
		void draw(buf& buffer, gMathLib::Vector2D<pointType> position, const std::string& text)
		{
			auto rectSize = gMathLib::Vector2D<pointType>(fontHeight.getValue(buffer.getWidth()) * 5, fontHeight.getValue(buffer.getWidth()));
			if (drawByCenter) position = position - rectSize * 0.5;
			drawBuffer2D::filledRectangle(buffer,
				position, 
				rectSize,
				colorSettings.outlineColor, 
				colorSettings.interiorColor);
			//TODO: add here realisations for draw text with only use coord and text
		}
	};

	template <typename color>
	struct GraphDrawSettings
	{
		settings settingsFlags;
		color backgroundColor = colorLib::RGBA8(0, 255, 0, 255);
		NodeDrawSettings<color> nodeType;
		LineDrawSettings<color> lineType;
		FontDrawSettings<color> fontType;
		SizePartType graphOffset = SizePartType(true, 0, 0.15);
		
		GraphDrawSettings(settings settingsFlags = settings::DRAW_NO_FLAGS) : settingsFlags(settingsFlags) {}
	};
	//
	//------------------------------| END SETTINGS|-------------------------------
	//
	
	//          _														_
	//----------|-----------| PART WHERE WE REALLY START DRAW |---------|---------
	//			V														V
	template <typename VECNODES, typename BUFTYPE, typename SETTINGSTYPE>
	void makePositionForBuffer(VECNODES& toChangeNodes, BUFTYPE& buffer, SETTINGSTYPE& flags)
	{
		double xMinPos = 1e+308;
		double xMaxPos = -1e+308;
		double yMinPos = 1e+308;
		double yMaxPos = -1e+308;
		for (const auto& el : toChangeNodes)
		{
			if (el.x_ < xMinPos) xMinPos = el.x_;
			if (el.x_ > xMaxPos) xMaxPos = el.x_;
			if (el.y_ < yMinPos) yMinPos = el.y_;
			if (el.y_ > yMaxPos) yMaxPos = el.y_;
		}
		double resizeCoef = 1.;
		double dxPos = xMaxPos - xMinPos;
		double dyPos = yMaxPos - yMinPos;
		auto centerOfGraph = gMathLib::Vector2D<double>((xMaxPos + xMinPos), (yMaxPos + yMinPos)) * 0.5;
		//TODO: chenge it for better working with width != height!
		if (((dxPos) != 0 or (dyPos) != 0) and toChangeNodes.size() != 0)
			resizeCoef = (dxPos > dyPos) ? (buffer.getWidth() / dxPos) : (buffer.getWidth() / dyPos);



		double partValue = flags.graphOffset.getPartValue(buffer.getWidth());

		if (0 > partValue) void();
		else if (0.5 < partValue) resizeCoef = 0;
		else resizeCoef = resizeCoef * (1. - 2 * partValue);

		for (auto& el : toChangeNodes)
		{
			el = el - centerOfGraph;
			el = el * resizeCoef;
			el = el + gMathLib::Vector2D<double>(buffer.getWidth() / 2, buffer.getWidth() / 2);
		}
		//TODO: add checking for dinamic changing node size dependenced by size, neaerst position and so on.
	}





	template <typename BUFTYPE, typename SETTINGSTYPE>
	void drawGraph(BUFTYPE& buffer, GraphObjectLib::GraphObject& graphToDraw, SETTINGSTYPE& flags)
	{
		auto Nodes = graphToDraw.getGraphNodes();
		makePositionForBuffer(Nodes, buffer, flags);

		if ((flags.settingsFlags & settings::NO_DRAW_BACKGROUND) == settings::DRAW_NO_FLAGS)
		{
			buffer.blitAll(flags.backgroundColor);
		}

		if ((flags.settingsFlags & settings::NO_DRAW_LINKS) == settings::DRAW_NO_FLAGS)
		{
			for (const auto& el : graphToDraw.getNodeLinks())
			{
				flags.lineType.draw(buffer, Nodes[el.first], Nodes[el.second]);
			}
		}

		if ((flags.settingsFlags & settings::NO_DRAW_NODES) == settings::DRAW_NO_FLAGS)
		{
			for (const auto& el : Nodes)
			{
				flags.nodeType.draw(buffer, el);
			}
		}

		if ((flags.settingsFlags & settings::NO_DRAW_NUMIRATION) == settings::DRAW_NO_FLAGS)
		{
			int i = 0;
			for (const auto& el : Nodes)
			{
				flags.fontType.draw(buffer, el, std::to_string(++i));
			}
		}

		return void();
	}
	//
	//-------------------------| END  PART WHERE WE DRAW|-------------------------------
	//
}


#endif // !_GRAPHPAINTER_INCLUDE_GRAPHDRAW_H_
