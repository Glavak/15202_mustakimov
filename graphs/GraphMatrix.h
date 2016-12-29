#pragma once

#include <stack>
#include <queue>

template<typename VertexType>
class Graph
{
public:
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

    std::vector<VertexType> getNeighbours(const VertexType & vertexA)
    {
        std::vector<VertexType> result;

        int a = getVertexIndex(vertexA);
        for (int i = 0; i < verticies.size(); ++i)
        {
            if (edgeMatrix[a][i])
            {
                result.push_back(verticies[i]);
            }
        }

        return result;
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
};