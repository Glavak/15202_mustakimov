#include <gtest/gtest.h>
#include <functional>
#include "../GraphMatrix.h"
#include "../Searches.h"

TEST(GraphMatrixTests, EdgesTest)
{
    Graph<int> graph;

    graph.addVertex(42);
    graph.addVertex(18);
    graph.addVertex(-11);

    graph.setEdge(42, 18, true);
    graph.setEdge(-11, 18, true);
    graph.setEdge(18, 42, false);

    ASSERT_FALSE(graph.getEdge(42, 18));
    ASSERT_FALSE(graph.getEdge(-11, 42));
    ASSERT_TRUE(graph.getEdge(-11, 18));
    ASSERT_ANY_THROW(graph.getEdge(18, 120));
}

TEST(GraphMatrixTests, GetNeighboursTest)
{
    Graph<int> graph;

    graph.addVertex(42);
    graph.addVertex(18);
    graph.addVertex(-11);

    graph.setEdge(42, 18, true);
    graph.setEdge(-11, 18, true);
    graph.setEdge(18, 42, false);

    std::vector<int> actual = graph.getNeighbours(18);
    std::vector<int> expected = {-11};

    ASSERT_EQ(expected, actual);
}