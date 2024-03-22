#include "../include/GraphSolver.h"
const double C1 = 2;
const double C2 = 1;
const double C3 = 1;
const double C4 = 0.1;
namespace graphToolsLib
{

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
        for (auto& el1 : graphNodes)
        {
            for (auto& el2 : graphNodes)
            {
                if (el1 != el2)
                {
                    auto dpos = el2 - el1;
                    auto length = dpos.getLength();
                    dpos.normalize();
                    el1 = el1 - dpos * (C3 / (length * length) * C4);
                    //el1.print();
                    //el1 = el1 + dpos * (C1 * log(length/(C2)));
                }
            }
        }
        for (const auto& [first, second] : nodeLinks)
        {
            auto& el1 = graphNodes[first];
            auto& el2 = graphNodes[second];
            if (el1 != el2)
            {
                auto dpos = el2 - el1;
                auto length = dpos.getLength();
                dpos.normalize();
                el1 = el1 + dpos * (C1 * log(length / (C2)) * C4);
                el2 = el2 - dpos * (C1 * log(length / (C2)) * C4);
            }
        }
        return GRAPH_SOLVER_ERROR::GRAPH_SOLWER_OK;
    }

    GRAPH_SOLVER_ERROR GraphSolver::get(GraphObjectLib::GraphObject& getGraph)
    {
        if (!this->isInit()) return GRAPH_SOLVER_ERROR::GRAPH_NO_INIT;
        //if it init we get it back.
        getGraph = std::move(static_cast<GraphObjectLib::GraphObject&>(*this));//can we do this?
        return GRAPH_SOLVER_ERROR::GRAPH_SOLWER_OK;
    }
}
