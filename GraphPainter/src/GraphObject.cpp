#include "../include/GraphObject.h"

using namespace GraphObjectLib;

GraphObjectLib::GraphObject::GraphObject(GraphObject&& other) noexcept
{
	*this = std::move(other);
}

GraphObject& GraphObjectLib::GraphObject::operator=(GraphObject&& other) noexcept
{
	if (this != &other)
	{
		this->graphNodes = std::move(other.graphNodes);
		this->nodeLinks = std::move(other.nodeLinks);
		this->_isInit = other.isInit();
		other._isInit = false;
	}
	return *this;
}

ERROR_GRAPH_FILE GraphObjectLib::GraphObject::loadGraph(const std::string& filename)
{
	//TODO: make loading file
	_isInit = true;
	return ERROR_GRAPH_FILE::GRAPH_FILE_OK;
}

void GraphObjectLib::GraphObject::freeGraph()
{
	this->graphNodes.clear();
	this->nodeLinks.clear();
	_isInit = false;
}

bool GraphObjectLib::GraphObject::isCorrectGraphData()
{
	int maxIndexElement = this->graphNodes.size() - 1;
	for (const auto& el : nodeLinks)
	{
		if (!(0 <= el.first and el.first <= maxIndexElement and
			0 <= el.second and el.second <= maxIndexElement)
			or (el.first == el.second))
			//TODO add checking for repeating links.
			return false;
	}
	return true;
}

