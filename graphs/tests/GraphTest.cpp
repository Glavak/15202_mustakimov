#include <gtest/gtest.h>
#include "../Graph.h"

TEST(GraphTests, EdgesTest)
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

TEST(GraphTests, DFSTest)
{
    Graph<int> graph;

    graph.addVertex(1); //(1)---- 2
    graph.addVertex(2); // |
    graph.addVertex(3); // |
    graph.addVertex(4); // 3 ---- 4

    graph.setEdge(1, 2, true);
    graph.setEdge(1, 3, true);
    graph.setEdge(3, 4, true);

    std::vector<int> actual;
    std::vector<int> expected = {1, 3, 4, 2};

    graph.DFS([&actual](int v)
              {
                  actual.push_back(v);
              }, 1);

    ASSERT_EQ(expected, actual);
}

TEST(GraphTests, BFSTest)
{
    Graph<int> graph;

    graph.addVertex(1); //(1)---- 2
    graph.addVertex(2); // |
    graph.addVertex(3); // |
    graph.addVertex(4); // 3 ---- 4

    graph.setEdge(1, 2, true);
    graph.setEdge(1, 3, true);
    graph.setEdge(3, 4, true);

    std::vector<int> actual;
    std::vector<int> expected = {1, 2, 3, 4};

    graph.BFS([&actual](int v)
              {
                  actual.push_back(v);
              }, 1);

    ASSERT_EQ(expected, actual);
}