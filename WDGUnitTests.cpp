#include <gtest/gtest.h>
#include "WeightedDirectedGraph.h"

TEST(WDGConstruction, constructTwoNodes)
{
    vector<Path> edges =
    {
        { 0, 1, 2 }
    };
    WeightedDirectedGraph graph(edges, 2);
    const vector<vector<pair<int, int>>>& matrix = graph.getAdjacencyMatrix();
    GTEST_ASSERT_EQ(matrix.size(), 2);
}

TEST(WDGPathSearch, FiveSizedNodeDijikstra)
{
    vector<Path> paths =
    {
        { 0, 1, 10 }, { 0, 2, 3 },
        { 1, 3, 2 }, { 1, 2, 1 },
        { 2, 1, 4 }, { 2, 4, 2 }, { 2, 3, 8 },
        { 3, 4, 7 }, 
        { 4, 3, 9 }
    };

    int expectedShortestPaths[] =
    {
        0, 7, 3, 9, 5
    };

    int actualShortestPaths[5];

    WeightedDirectedGraph graph(paths, 5);
    graph.findShortestPathDijkstra(0, actualShortestPaths); 
    for(int i = 0; i < graph.getNumberOfNodes(); i++)                      
    { 
        GTEST_ASSERT_EQ(expectedShortestPaths[i], actualShortestPaths[i]);
    }
}

TEST(WDGAcyclic, AcyclicGraph)
{
    vector<Path> paths =
    {
        { 0, 1, 1 }, //1
        { 1, 2, 1 }, { 1, 3, 1 }, //2
        //3
        { 3, 5, 1 }, { 3, 4, 1 }, //4
        { 4, 5, 1 }, //5
        { 5, 2, 1 }//6
    };

    WeightedDirectedGraph graph(paths, 6);

    GTEST_ASSERT_EQ(graph.isGraphAcyclic(), true);
}

TEST(WDGCyclic, CyclicGraph)
{
    vector<Path> paths =
    {
        { 0, 1, 1 }, //1
        { 1, 2, 1 }, { 1, 3, 1 }, //2
        //3
        { 3, 4, 1 }, //4
        { 4, 5, 1 }, //5
        { 5, 2, 1 }, { 5, 3, 1 }//6
    };

    WeightedDirectedGraph graph(paths, 6);

    GTEST_ASSERT_EQ(graph.isGraphAcyclic(), false);
}

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}