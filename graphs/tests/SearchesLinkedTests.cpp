#include <gtest/gtest.h>
#include <functional>
#include "../GraphMatrix.h"
#include "../Searches.h"
#include "../GraphLinked.h"

class SearchesLinkedTests : public ::testing::Test
{
protected:
    void SetUp()
    {
        v1.content = 1; //(1)---- 2
        v2.content = 2; // |
        v3.content = 3; // |
        v4.content = 4; // 3 ---- 4

        v1.neigbours.push_back(&v2);
        v1.neigbours.push_back(&v3);

        v2.neigbours.push_back(&v1);

        v3.neigbours.push_back(&v1);
        v3.neigbours.push_back(&v4);

        v4.neigbours.push_back(&v3);
    }

    void TearDown()
    {

    }

    Vertex<int> v1;
    Vertex<int> v2;
    Vertex<int> v3;
    Vertex<int> v4;
};

TEST_F(SearchesLinkedTests, DFSTest)
{
    std::vector<int> actual;
    std::vector<int> expected = {1, 3, 4, 2};

    auto getNeighbours = [](Vertex<int> * v)
    {
        return v->neigbours;
    };

    auto forEach = [&actual](Vertex<int> * v)
    {
        actual.push_back(v->content);
    };

    Searches::DFS(getNeighbours, forEach, &v1);

    ASSERT_EQ(expected, actual);
}

TEST_F(SearchesLinkedTests, BFSTest)
{
    std::vector<int> actual;
    std::vector<int> expected = {1, 2, 3, 4};

    auto getNeighbours = [](Vertex<int> * v)
    {
        return v->neigbours;
    };

    auto forEach = [&actual](Vertex<int> * v)
    {
        actual.push_back(v->content);
    };

    Searches::BFS(getNeighbours, forEach, &v1);

    ASSERT_EQ(expected, actual);
}