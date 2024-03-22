#ifndef _GRAHP_OBJECT_H_
#define _GRAHP_OBJECT_H_
#include <vector>
#include "../linker.h"

namespace GraphObjectLib
{
	enum ERROR_GRAPH_FILE
	{
		GRAPH_FILE_OK,
		GRAPH_FILE_NO_EXIST,
		GRAPH_FILE_INVALID_SIMBOLOS
	};
	struct GraphObject
	{
	protected:
		std::vector<gMathLib::Vector2D<float>> graphNodes;
		std::vector<std::pair<int, int>> nodeLinks;
		bool _isInit = false;
	public:
		GraphObject(GraphObject&& other) noexcept;
		GraphObject() = default;
		GraphObject& operator=(GraphObject&& other) noexcept;

		ERROR_GRAPH_FILE loadGraph(const std::string& filename);

		bool isInit() { return _isInit; }

		void freeGraph();

		bool isCorrectGraphData();

		void print();
		//for incapsulating read.
		const std::vector<gMathLib::Vector2D<float>>& getGraphNodes() const {return graphNodes;}

		const std::vector<std::pair<int, int>>& getNodeLinks() const {return nodeLinks;}
	};
}



#endif // !_GRAHP_OBJECT_H_
