#include "dw_graph.h"
#include <iostream>
#include <algorithm>
#include <set>
#include <queue>
#include <climits>

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

void dijkstra(DirectedWeightedGraph graph, vector<int> &allDistances, int source)
{
    int nodeCount = graph.get_nodeCount();
    // Create set to store vertices
    // Use this to extract the shortest path
    set<pair<int, int>> nodes;

    // Vector for distances
    // All paths are initialized to a large value
    vector<int> distances(nodeCount, INT_MAX);

    // Insert the entry point into the set
    // Initialize distance to 0
    nodes.insert(make_pair(0, source));
    distances[source] = 0;

    // Continue until all shortest distances are finalized
    while (!nodes.empty())
    {
        // Extract the minimum distances
        pair<int, int> temporaryNode = *(nodes.begin());
        nodes.erase(nodes.begin());

        // Get the vertex number
        int source = temporaryNode.second;

        // Go over the adjacency list
        for (auto i = graph.adjacencyList[source].begin(); i != graph.adjacencyList[source].end(); i++)
        {
            // Get the vertex and weight
            int currentDestination = (*i).first;
            int weight = (*i).second;

            // Check if we have found a shorter path to v
            if (distances[currentDestination] > distances[source] + weight)
            {

                // Remove the current distance if it is in the set
                if (distances[currentDestination] != INT_MAX)
                {
                    nodes.erase(nodes.find(make_pair(distances[currentDestination], currentDestination)));
                }

                // Update the distance
                distances[currentDestination] = distances[source] + weight;
                nodes.insert(make_pair(distances[currentDestination], currentDestination));
            }
        }
    }

    allDistances = distances;
}