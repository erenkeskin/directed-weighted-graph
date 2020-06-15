#include "dw_graph.h"
#include <iostream>

using namespace std;

DirectedWeightedGraph::DirectedWeightedGraph()
{
}

DirectedWeightedGraph::DirectedWeightedGraph(vector<Edge> &edges, int nodeCount)
{
    set_nodeCount(nodeCount);
    adjacencyList.resize(this->get_nodeCount());
    for (auto edge : edges)
    {
        adjacencyList[edge.source].push_back(make_pair(edge.destination, edge.weight));
    }
}

DirectedWeightedGraph::DirectedWeightedGraph(int nodeCount)
{
    set_nodeCount(nodeCount);
    adjacencyList.resize(this->get_nodeCount());
}

DirectedWeightedGraph::~DirectedWeightedGraph()
{
    // for (size_t n = 0; n < adjacencyList.size(); ++n)
    // {
    //     delete &adjacencyList[n];
    // }
    // delete &adjacencyList;
}
 
void DirectedWeightedGraph::add_edge(int source, int destination, int weight)
{
    adjacencyList.resize(this->get_nodeCount());
    adjacencyList[source].push_back(make_pair(destination, weight));
}

void DirectedWeightedGraph::add_edge(vector<Edge> &edges)
{
    adjacencyList.resize(this->get_nodeCount());
    for (auto edge : edges)
    {
        adjacencyList[edge.source].push_back(make_pair(edge.destination, edge.weight));
    }
}