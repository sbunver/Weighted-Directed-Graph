#include <iostream>
#include <vector>
using namespace std;
 
struct Path {
    int node;
    int destination;
    int weight;
};

class WeightedDirectedGraph
{
public:
    WeightedDirectedGraph(vector<Path> const &paths, int numOfNodes);
    const vector<vector<pair<int, int>>>& getAdjacencyMatrix() const;
    void findShortestPathDijkstra(int sourceNode, int nodeDistance[]);
    int getNumberOfNodes() const;
    bool isGraphAcyclic();
private:
    vector<vector<pair<int, int>>> adjacencyMatrix;
    int NUMBER_OF_NODES = 0;
    bool hasAPath(int fromNode, int toNode);
    int getPathWeight(int fromNode, int toNode);
    int getMinDistIndex(int nodeDistance[], bool nodeVisited[]);
    bool isAShortestPath(int nodeDistance[], int currentNode, int toNode);
    int getLeafNode(vector<vector<pair<int, int>>> testedadjMatrix, bool *nodeRemoved);
    bool isAllNodesRemoved(bool *nodeRemoved);
};