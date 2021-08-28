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
    WeightedDirectedGraph(vector<Path> const &paths, int numOfElement)
    {
        adjacencyMatrix.reserve(numOfElement);
        for (auto &path: paths)
        {
            adjacencyMatrix[path.node].
                push_back(make_pair(path.destination, path.weight));
        }
    }
    
    const vector<vector<pair<int, int>>>& getAdjacencyMatrix() const
    {
        return adjacencyMatrix;
    }

private:
    vector<vector<pair<int, int>>> adjacencyMatrix;
};