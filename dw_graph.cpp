#include "dw_graph.h"
#include <iostream>
#include <algorithm>

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

int DirectedWeightedGraph::add_edge(int source, int destination, int weight)
{
    adjacencyList.resize(this->get_nodeCount());
    adjacencyList[source].push_back(make_pair(destination, weight));

    return 0;
}

int DirectedWeightedGraph::add_edge(vector<Edge> &edges)
{
    adjacencyList.resize(this->get_nodeCount());
    for (auto edge : edges)
    {
        adjacencyList[edge.source].push_back(make_pair(edge.destination, edge.weight));
    }

    return 0;
}

int DirectedWeightedGraph::remove_edge(int source, int destination)
{
    int index;

    for (int i = 0; i < adjacencyList[source].size(); i++)
    {
        if (adjacencyList[source][i].first == destination)
        {
            index = i;
            break;
        }
    }

    cout << "Position:" << index << endl;

    adjacencyList[source].erase(adjacencyList[source].begin() + index);

    return 0;
}

bool DirectedWeightedGraph::is_edge(int source, int destination)
{

    for (int i = 0; i < adjacencyList[source].size(); i++)
    {
        if (adjacencyList[source][i].first == destination)
        {
            return true;
        }
    }
    return false;
}