#pragma once
#ifndef _GRAPHPAINTER_INCLUDE_GRAPHDRAW_H_
#define _GRAPHPAINTER_INCLUDE_GRAPHDRAW_H_
#include "GraphObject.h"
namespace graphDrawLib
{

	template <typename color>
	struct ShapeDrawSettings
	{
		color outlineColor = (0, 0, 0, 255);
		color interiorColor = (255, 255, 255, 255);
		float outlineWidth = 1;
	};

	template <typename color>
	struct FontDrawSettings
	{
	};

	template <typename color>
	struct GraphDrawSettings
	{
		color backgroundColor;
		ShapeDrawSettings nodeColorSettings;
		ShapeDrawSettings lineColorSettings;
		bool doNodeNumeration = true;
		FontDrawSettings fontSettings;
		

	};
	template <typename BUFTYPE, typename SETTINGSTYPE>
	void drawGraph(BUFTYPE& buffer, GraphObjectLib::GraphObject& graphToDraw,   SETTINGSTYPE& flags)
	{
		//
		//dependence to graphics font h
	}
}


#endif // !_GRAPHPAINTER_INCLUDE_GRAPHDRAW_H_
