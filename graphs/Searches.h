//
// Created by glavak on 24.12.16.
//

#ifndef GRAPHS_DFS_H
#define GRAPHS_DFS_H

#include <algorithm>
#include <set>
#include <deque>

class Searches
{
    template<
            typename GetNeighboursFunction,
            typename ForEachFunction,
            typename VertexType>
    static void search(GetNeighboursFunction getNeighbours,
                       ForEachFunction forEach,
                       VertexType startingVertex,
                       bool isDFS)
    {
        VertexType currentVertex = startingVertex;

        std::deque<VertexType> stack;
        std::set<VertexType> visited;

        stack.push_back(currentVertex);

        while (!stack.empty())
        {
            if (isDFS)
            {
                currentVertex = stack.back();
                stack.pop_back();
            }
            else
            {
                currentVertex = stack.front();
                stack.pop_front();
            }

            if (std::find(visited.begin(), visited.end(), currentVertex) != visited.end())
            {
                // Visited vertex
                continue;
            }

            forEach(currentVertex);
            visited.insert(currentVertex);

            for (VertexType neighbour : getNeighbours(currentVertex))
            {
                stack.push_back(neighbour);
            }
        }
    }

public:

    template<
            typename GetNeighboursFunction,
            typename ForEachFunction,
            typename VertexType>
    static void DFS(GetNeighboursFunction getNeighbours,
             ForEachFunction forEach,
             VertexType startingVertex)
    {
        search(getNeighbours, forEach, startingVertex, true);
    }

    template<
            typename GetNeighboursFunction,
            typename ForEachFunction,
            typename VertexType>
    static void BFS(GetNeighboursFunction getNeighbours,
             ForEachFunction forEach,
             VertexType startingVertex)
    {
        search(getNeighbours, forEach, startingVertex, false);
    }
};

#endif //GRAPHS_DFS_H
