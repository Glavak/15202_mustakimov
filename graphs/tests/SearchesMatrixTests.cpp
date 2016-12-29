#include <gtest/gtest.h>
#include <functional>
#include "../GraphMatrix.h"
#include "../Searches.h"

class SearchesMatrixTests : public ::testing::Test
{
protected:
    void SetUp()
    {
        graph.addVertex(1); //(1)---- 2
        graph.addVertex(2); // |
        graph.addVertex(3); // |
        graph.addVertex(4); // 3 ---- 4

        graph.setEdge(1, 2, true);
        graph.setEdge(1, 3, true);
        graph.setEdge(3, 4, true);
    }

    void TearDown()
    {

    }

    Graph<int> graph;
};

TEST_F(SearchesMatrixTests, DFSTest)
{
    std::vector<int> actual;
    std::vector<int> expected = {1, 3, 4, 2};

    auto getNeighbours = [this](int v)
    {
        return graph.getNeighbours(v);
    };

    auto forEach = [&actual](int v)
    {
        actual.push_back(v);
    };

    Searches::DFS(getNeighbours, forEach, 1);

    ASSERT_EQ(expected, actual);
}

TEST_F(SearchesMatrixTests, BFSTest)
{
    std::vector<int> actual;
    std::vector<int> expected = {1, 2, 3, 4};

    auto getNeighbours = [this](int v)
    {
        return graph.getNeighbours(v);
    };

    auto forEach = [&actual](int v)
    {
        actual.push_back(v);
    };

    Searches::BFS(getNeighbours, forEach, 1);

    ASSERT_EQ(expected, actual);
}