#pragma once

#include <stack>
#include <queue>

template<typename VertexType>
class Graph
{
public:
    template<typename Function>
    void DFS(Function function, const VertexType & vertexBegin)
    {
        graphSearch(function, vertexBegin, true);
    }

    template<typename Function>
    void BFS(Function function, const VertexType & vertexBegin)
    {
        graphSearch(function, vertexBegin, false);
    }

    void addVertex(const VertexType & vertex)
    {
        verticies.push_back(vertex);

        edgeMatrix.push_back(std::vector<bool>(verticies.size()));
        for (int i = 0; i < verticies.size() - 1; ++i)
        {
            edgeMatrix[i].push_back(false);
        }
    }

    void setEdge(const VertexType & vertexA, const VertexType & vertexB, bool edge)
    {
        int a = getVertexIndex(vertexA);
        int b = getVertexIndex(vertexB);
        edgeBetweenVerticies(a, b) = edge;
        edgeBetweenVerticies(b, a) = edge;
    }

    bool getEdge(const VertexType & vertexA, const VertexType & vertexB)
    {
        int a = getVertexIndex(vertexA);
        int b = getVertexIndex(vertexB);
        return edgeBetweenVerticies(b, a);
    }

private:
    std::vector<VertexType> verticies;
    std::vector<std::vector<bool>> edgeMatrix;

    int getVertexIndex(const VertexType & vertex)
    {
        for (int i = 0; i < verticies.size(); ++i)
        {
            if (verticies[i] == vertex)
            {
                return i;
            }
        }

        throw "vertex not found";
    }

    std::_Bit_reference edgeBetweenVerticies(int vertexA, int vertexB)
    {
        return edgeMatrix[vertexA][vertexB];
    }

    template<typename Function>
    void graphSearch(Function function, const VertexType & vertexBegin, bool useStack)
    {
        int currentVertexIndex = getVertexIndex(vertexBegin);

        std::deque<int> stack;
        std::set<int> visited;
        stack.push_back(currentVertexIndex);

        while (!stack.empty())
        {
            if(useStack)
            {
                currentVertexIndex = stack.back();
                stack.pop_back();
            }
            else
            {
                currentVertexIndex = stack.front();
                stack.pop_front();
            }

            if (std::find(visited.begin(), visited.end(), currentVertexIndex) != visited.end())
            {
                // Visited vertex
                continue;
            }

            function(verticies[currentVertexIndex]);
            visited.insert(currentVertexIndex);

            for (int i = 0; i < verticies.size(); ++i)
            {
                if (edgeMatrix[currentVertexIndex][i])
                {
                    stack.push_back(i);
                }
            }
        }
    }
};