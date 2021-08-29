#include <climits>
#include "WeightedDirectedGraph.h"

WeightedDirectedGraph::WeightedDirectedGraph(vector<Path> const &paths, int numOfNodes)
{
        NUMBER_OF_NODES = numOfNodes;
        adjacencyMatrix.resize(NUMBER_OF_NODES);
        for (auto& path: paths)
        {
            adjacencyMatrix[path.node].
                push_back(make_pair(path.destination, path.weight));
        }
}

const vector<vector<pair<int, int>>>& WeightedDirectedGraph::getAdjacencyMatrix() const
{
        return adjacencyMatrix;
}

int WeightedDirectedGraph::getNumberOfNodes() const
{
        return NUMBER_OF_NODES;
}

int WeightedDirectedGraph::getMinDistIndex(int nodeDistance[], bool nodeVisited[])
{
    int minimum = INT_MAX;
    int index = 0;
              
    for(int node = 0; node < adjacencyMatrix.size(); node++) 
    {
        if(nodeVisited[node] == false && nodeDistance[node] <= minimum)      
        {
            minimum = nodeDistance[node];
            index = node;
        }
    }
    return index;
}

bool WeightedDirectedGraph::hasAPath(int fromNode, int toNode)
{
        if(adjacencyMatrix[fromNode].size() > 0)
        {
                for(auto& v : adjacencyMatrix[fromNode])
                {
                        if(v.first == toNode)
                        {
                                return true;
                        }
                }
        }
        return false;
}

int WeightedDirectedGraph::getPathWeight(int fromNode, int toNode)
{
        if(adjacencyMatrix[fromNode].size() > 0)
        {
                for(auto& v : adjacencyMatrix[fromNode])
                {
                        if(v.first == toNode)
                        {
                                return v.second;
                        }
                }
        }
        return 0;
}

bool WeightedDirectedGraph::isAShortestPath(int nodeDistance[], int currentNode, int toNode)
{
    return nodeDistance[currentNode] + 
        getPathWeight(currentNode, toNode) < nodeDistance[toNode];
}

void WeightedDirectedGraph::findShortestPathDijkstra(int sourceNode, int nodeDistance[])
{                            
    bool nodeVisited[NUMBER_OF_NODES];
   
    for(int i = 0; i < NUMBER_OF_NODES; i++)
    {
        nodeDistance[i] = INT_MAX;
        nodeVisited[i] = false;    
    }
    nodeDistance[sourceNode] = 0;            
    
    for(int toNode = 0; toNode < NUMBER_OF_NODES; toNode++)                           
    {
        int currentNode = getMinDistIndex(nodeDistance, nodeVisited); 
        int currentNodeDistance = nodeDistance[currentNode];
        nodeVisited[currentNode] = true;
        for(int toNode = 0; toNode < NUMBER_OF_NODES; toNode++)                  
        {
            if
            (
                !nodeVisited[toNode] && 
                hasAPath(currentNode, toNode) && 
                currentNodeDistance != INT_MAX && 
                isAShortestPath(nodeDistance, currentNode, toNode)
            )
            {
                int weight = getPathWeight(currentNode, toNode);
                nodeDistance[toNode] = currentNodeDistance + weight;
            }

               
        }
    }
}
