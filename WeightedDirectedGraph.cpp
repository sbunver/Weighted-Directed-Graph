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
    pair<int, int> desiredPath;

    for(auto& v : adjacencyMatrix[fromNode])
    {
        if(v.first == toNode)
        {
            desiredPath = v;
        }
    }
    return desiredPath.second;
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

int WeightedDirectedGraph::getLeafNode(vector<vector<pair<int, int>>> testedadjMatrix, bool nodeRemoved[])
{
    for(int i = 0; i < testedadjMatrix.size(); i++)
    {
            if(testedadjMatrix[i].size() == 0 && !nodeRemoved[i])
            {
                    return i;
            }
    }
    return -1;
}

void removeLeafNode(vector<vector<pair<int, int>>>& testedadjMatrix, int removeNode, bool *nodeRemoved)
{
    for(auto& node : testedadjMatrix)
    {
            vector<pair<int, int>>::iterator it1 = node.begin();
            nodeRemoved[removeNode] = true;
            for(int path = 0; path < node.size(); path++)
            {
                if(node[path].first == removeNode)
                {
                node.erase(it1);
                }
                it1++;
            }
    }
}

bool WeightedDirectedGraph::isAllNodesRemoved(bool *nodeRemoved)
{
    for(int i = 0; i < NUMBER_OF_NODES; i++)
    {
        if(nodeRemoved[i] == false)
        {
            return false;
        }    
    }
    return true;
}

bool WeightedDirectedGraph::isGraphAcyclic()
{
    vector<vector<pair<int, int>>> testedadjMatrix = adjacencyMatrix;
    int leafNodeIndex = 0;
    bool nodeRemoved[NUMBER_OF_NODES];

    for(int i = 0; i < NUMBER_OF_NODES; i++)
    {
        nodeRemoved[i] = false;    
    }

    while(1)
    {
        if(isAllNodesRemoved(nodeRemoved))
        {
            return true;
        }

        leafNodeIndex = getLeafNode(testedadjMatrix, nodeRemoved);
       
        if(leafNodeIndex < 0)
        {
            return false;
        }

        removeLeafNode(testedadjMatrix, leafNodeIndex, nodeRemoved);

    }
    return false;
}