#include "../include/GraphObject.h"
#include <iostream>
#include <fstream>
#include <string>
#define RANDOM(toRandomize) toRandomize = (std::rand()%212) * 0.1
namespace GraphObjectLib
{

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
		this->nodeLinks.clear();
		std::string line;
		std::vector<int> data;
		std::ifstream GraphTxtFile(filename);
		if (!GraphTxtFile.is_open()) return ERROR_GRAPH_FILE::GRAPH_FILE_NO_EXIST;

		while (GraphTxtFile >> line)
		{
			if (!std::all_of(line.begin(), line.end(), ::isdigit)) return ERROR_GRAPH_FILE::GRAPH_FILE_INVALID_SIMBOLOS;
			data.push_back(std::stoi(line));
		}
		if (data.size() % 2 == 1 or data.size() < 2) return ERROR_GRAPH_FILE::GRAPH_FILE_INVALID_SIMBOLOS;
		for (int i = -(int)(data.size() *0.5) + 1; i < 0; i++)
		{
			this->nodeLinks.push_back(std::pair<int, int>(data[data.size() - 2] - 1, data[data.size() - 1] - 1));
			data.pop_back();
			data.pop_back();
		}

		this->graphNodes.resize(data[0]);
		std::for_each(this->graphNodes.begin(), this->graphNodes.end(), [](auto& el) {RANDOM(el.x_); RANDOM(el.y_); });
		if (!this->isCorrectGraphData())
		{
			this->graphNodes.clear();
			this->nodeLinks.clear();
			return ERROR_GRAPH_FILE::GRAPH_FILE_INVALID_SIMBOLOS;
		}
		GraphTxtFile.close();
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

	void GraphObject::print()
	{
		std::cout << "[ isInit: " << (this->_isInit ? "TRUE" : "FALSE") << " ]\n";
		std::cout << "[ Nodes: " <<  this->graphNodes.size() << " ]\n[ Links:\n";
		for (auto [first, second] : this->nodeLinks)
			std::cout << "(" << first+1 << "\t-" << second+1 << "\t)\n";
		std::cout << "]\n";
	}

}