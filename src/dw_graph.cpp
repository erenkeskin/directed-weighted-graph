#include "../include/dw_graph.h"
#include <iostream>
#include <set>
#include <queue>
#include <climits>

using namespace std;

DirectedWeightedGraph::DirectedWeightedGraph() {}

DirectedWeightedGraph::DirectedWeightedGraph(int nodeCount)
{
    set_nodeCount(nodeCount);
    adjacencyList.resize(this->get_nodeCount());
}

DirectedWeightedGraph::DirectedWeightedGraph(vector<Edge> &edges, int nodeCount)
{

    set_nodeCount(nodeCount);
    adjacencyList.resize(this->get_nodeCount());

    for (auto edge : edges)
    {
        if (existance_check(edges) != 0)
        {
            return;
        }
        adjacencyList[edge.source].push_back(make_pair(edge.destination, edge.weight));
    }
}

DirectedWeightedGraph::~DirectedWeightedGraph()
{
    for (size_t n = 0; n < adjacencyList.size(); ++n)
    {
        adjacencyList[n].clear();
        adjacencyList[n].shrink_to_fit();
    }
}

void DirectedWeightedGraph::set_nodeCount(int nodeCount)
{
    totalNodeCount = nodeCount;
    adjacencyList.resize(totalNodeCount);
};

int DirectedWeightedGraph::get_nodeCount(void)
{
    return totalNodeCount;
};

int DirectedWeightedGraph::existance_check(int source, int destination)
{
    int nodeCount = get_nodeCount();

    //
    if (nodeCount == -1)
    {
        return GRAPH_HAS_NOT_ANY_NODE;
    }

    //
    if (source >= nodeCount)
    {
        return SOURCE_NODE_NOT_EXIST;
    }

    //
    if (destination >= nodeCount)
    {
        return DESTINATION_NODE_NOT_EXIST;
    }

    return SUCCESS;
}

int DirectedWeightedGraph::existance_check(vector<Edge> &edges)
{
    int nodeCount = get_nodeCount();

    //
    if (nodeCount == -1)
    {
        return GRAPH_HAS_NOT_ANY_NODE;
    }

    for (auto edge : edges)
    {
        //
        if (edge.source >= nodeCount)
        {
            return SOURCE_NODE_NOT_EXIST;
        }

        //
        if (edge.destination >= nodeCount)
        {
            return DESTINATION_NODE_NOT_EXIST;
        }
    }

    return SUCCESS;
}

int DirectedWeightedGraph::add_edge(int source, int destination, int weight)
{
    int exist = existance_check(source, destination);

    if (exist != SUCCESS)
    {
        return exist;
    }

    //
    for (int i = 0; i < adjacencyList[source].size(); i++)
    {
        if ((adjacencyList[source][i].first == destination) && (adjacencyList[source][i].second == weight))
        {
            return ALREADY_EXIST;
        }
        adjacencyList[source].push_back(make_pair(destination, weight));
    }

    adjacencyList.resize(this->get_nodeCount());
    adjacencyList[source].push_back(make_pair(destination, weight));

    return SUCCESS;
}

int DirectedWeightedGraph::add_edge(vector<Edge> &edges)
{
    int exist = existance_check(edges);

    if (exist != SUCCESS)
    {
        return exist;
    }

    adjacencyList.resize(this->get_nodeCount());

    for (auto edge : edges)
    {
        for (int i = 0; i < adjacencyList[edge.source].size(); i++)
        {
            if ((adjacencyList[edge.source][i].first == edge.destination) && (adjacencyList[edge.source][i].second == edge.weight))
            {
                return ALREADY_EXIST;
            }
        }
        adjacencyList[edge.source].push_back(make_pair(edge.destination, edge.weight));
    }

    return SUCCESS;
}

int DirectedWeightedGraph::remove_edge(int source, int destination)
{
    int exist = existance_check(source, destination);

    if (exist != SUCCESS)
    {
        return exist;
    }

    if (!is_edge(source, destination))
    {
        return EDGE_NOT_EXIST;
    }

    int index;

    for (int i = 0; i < adjacencyList[source].size(); i++)
    {
        if (adjacencyList[source][i].first == destination)
        {
            index = i;
            break;
        }
    }

    adjacencyList[source].erase(adjacencyList[source].begin() + index);

    return SUCCESS;
}

bool DirectedWeightedGraph::is_edge(int source, int destination)
{
    int exist = existance_check(source, destination);

    if (exist != SUCCESS)
    {
        return false;
    }

    for (int i = 0; i < adjacencyList[source].size(); i++)
    {
        if (adjacencyList[source][i].first == destination)
        {
            return true;
        }
    }
    return false;
}

int dijkstra(DirectedWeightedGraph graph, vector<int> &allDistances, int source)
{
    int nodeCount = graph.get_nodeCount();

    //
    if (nodeCount == -1)
    {
        return GRAPH_HAS_NOT_ANY_NODE;
    }
    //
    if (source >= nodeCount)
    {
        return SOURCE_NODE_NOT_EXIST;
    }

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

    return SUCCESS;
}

int dijkstra(DirectedWeightedGraph graph, int source, int destination)
{
    int nodeCount = graph.get_nodeCount();

    int exist = graph.existance_check(source, destination);

    if (exist != SUCCESS)
    {
        return exist;
    }

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

    // Shortest path weight from source to destination
    return distances[destination];
}

// This function is a variation of DFSUtil() in https://www.geeksforgeeks.org/archives/18212
bool DirectedWeightedGraph::is_acyclicGraph(int visitingNode, bool visitedNode[], bool *recursiveStack)
{
    if (visitedNode[visitingNode] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visitedNode[visitingNode] = true;
        recursiveStack[visitingNode] = true;

        // Recur for all the vertices adjacent to this vertex
        for (auto i = adjacencyList[visitingNode].begin(); i != adjacencyList[visitingNode].end(); i++)
        {
            if (!visitedNode[(*i).first] && is_acyclicGraph((*i).first, visitedNode, recursiveStack))
            {
                return true;
            }
            if (recursiveStack[(*i).first])
            {
                return true;
            }
        }
    }
    recursiveStack[visitingNode] = false; // remove the vertex from recursion stack
    return false;
}

// Returns true if the graph contains a cycle, else false.
bool DirectedWeightedGraph::is_acyclic(void)
{
    // Mark all the vertices as not visited and not part of recursion
    // stack
    int nodeCount = get_nodeCount();
    bool *visitedNode = new bool[nodeCount];
    bool *recursiveStack = new bool[nodeCount];

    for (int i = 0; i < nodeCount; i++)
    {
        visitedNode[i] = false;
        recursiveStack[i] = false;
    }

    // Call the recursive helper function to detect cycle in different
    for (int i = 0; i < nodeCount; i++)
    {
        if (is_acyclicGraph(i, visitedNode, recursiveStack))
        {
            return true;
        }
    }

    return false;
}

void printGraph(DirectedWeightedGraph graph)
{
    for (int i = 0; i < graph.get_nodeCount(); i++)
    {
        cout << "Source: " << i << " -> ";
        for (auto p : graph.adjacencyList[i])
        {
            cout << "(Destination: " << p.first << ", Weight: " << p.second << ") ";
        }
        cout << endl;
    }
}