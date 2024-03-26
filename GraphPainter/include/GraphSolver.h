#ifndef _GRAPHPAINTER_INCLUDE_GRAPHTOOLS_H_
#define _GRAPHPAINTER_INCLUDE_GRAPHTOOLS_H_
#include "GraphObject.h"

namespace graphToolsLib
{
	enum GRAPH_SOLVER_ERROR
	{
		GRAPH_NO_INIT,
		INVALID_GRAPH_DATA, // data in graphObject was changed or something like that.
		GRAPH_SOLWER_HAD_NO_REFERENCE_TO_DATA,
		GRAPH_SOLWER_OK
	};
	class GraphSolver: public GraphObjectLib::GraphObject
	{
	private:
		GRAPH_SOLVER_ERROR solveBySprings();

	public:

		GRAPH_SOLVER_ERROR init(GraphObjectLib::GraphObject&& toSolveGraph);

		GRAPH_SOLVER_ERROR solve()
		{
			for (int i = 0; i < 30; i++)
				solveBySprings();
			return solveBySprings();
		}

		GRAPH_SOLVER_ERROR get(GraphObjectLib::GraphObject& getGraph);
	};

}

#endif // !_GRAPHPAINTER_INCLUDE_GRAPHTOOLS_H_
