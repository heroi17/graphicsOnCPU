#include "../include/GraphSolver.h"
using namespace graphToolsLib;
GRAPH_SOLVER_ERROR GraphSolver::init(GraphObjectLib::GraphObject&& toSolveGraph)
{
    if (!toSolveGraph.isInit())         return GRAPH_SOLVER_ERROR::GRAPH_NO_INIT;
    if (!toSolveGraph.isCorrectGraphData())   return GRAPH_SOLVER_ERROR::INVALID_GRAPH_DATA;




    static_cast<GraphObjectLib::GraphObject&>(*this) = std::move(toSolveGraph);//can we do this?





    return GRAPH_SOLVER_ERROR::GRAPH_SOLWER_OK;

}

GRAPH_SOLVER_ERROR GraphSolver::solve()
{
    if (!this->isInit()) return GRAPH_SOLVER_ERROR::GRAPH_NO_INIT;
    //TODO: make solution.
    return GRAPH_SOLVER_ERROR::GRAPH_SOLWER_OK;
}

GRAPH_SOLVER_ERROR GraphSolver::get(GraphObjectLib::GraphObject& getGraph)
{
    if (!this->isInit()) return GRAPH_SOLVER_ERROR::GRAPH_NO_INIT;
    //if it init we get it back.
    getGraph = std::move(static_cast<GraphObjectLib::GraphObject&>(*this));//can we do this?
    return GRAPH_SOLVER_ERROR::GRAPH_SOLWER_OK;
}


