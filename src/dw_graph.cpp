#include "../include/dw_graph.h"
#include <iostream>
#include <set>
#include <queue>
#include <climits>

using namespace std;

/**
 * Constructor without any parameter
 */
DirectedWeightedGraph::DirectedWeightedGraph() {}

/**
 * Constructor with node count
 *
 * @param nodeCount Node count for Graph
 * Setting node count for Graph and resize adjacency list
 */
DirectedWeightedGraph::DirectedWeightedGraph(int nodeCount)
{
    set_nodeCount(nodeCount);
    adjacencyList.resize(this->get_nodeCount());
}

/**
 * Constructor with edge list and node count
 *
 * @param edges Vector list for edges
 * @param nodeCount Node count for Graph
 * Setting node count for Graph
 * Resize adjacency list and
 * Fill all possible cell of adjacency list with edge items
 */
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

/**
 * Destructor of Graph for memory usage
 *
 * Delete all items in Graph and set size again
 */
DirectedWeightedGraph::~DirectedWeightedGraph()
{
    for (size_t n = 0; n < adjacencyList.size(); ++n)
    {
        adjacencyList[n].clear();
        adjacencyList[n].shrink_to_fit();
    }
}

/**
 * Setting node count for Graph
 *
 * @param nodeCount Node count for Graph
 * Setting node count for Graph
 * Resize adjacency list and
 */
void DirectedWeightedGraph::set_nodeCount(int nodeCount)
{
    totalNodeCount = nodeCount;
    adjacencyList.resize(totalNodeCount);
};

/**
 * Getting total node count from Graph
 *
 * @return total node count Vector list for edges
 */
int DirectedWeightedGraph::get_nodeCount(void)
{
    return totalNodeCount;
};

/**
 * Checking edge exist from source to destination
 *
 * @param source for start of the control
 * @param destination for finish of the control
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if destination is not exist DESTINATION_NODE_NOT_EXIST => -4,
 * @return if edge is exist SUCCESS => 0
 */
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

/**
 * Checking edge exist from source to destination
 *
 * @param edges for listing all nodes
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if parameter edge source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if parameteredge destination is not exist DESTINATION_NODE_NOT_EXIST => -4,
 * @return if edge is exist SUCCESS => 0
 */
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

/**
 * Adding new edge from source to destination with weight
 *
 * @param source 'from' part of the adding
 * @param destination 'to' part of the adding
 * @param weight weight from source to destination
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if destination is not exist DESTINATION_NODE_NOT_EXIST => -4,
 * @return if new edge is added SUCCESS => 0
 */
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

/**
 * Adding new edges with list of edge
 *
 * @param edges for listing all nodes
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if destination is not exist DESTINATION_NODE_NOT_EXIST => -4,
 * @return if parameter edges has duplicated edge ALREADY_EXIST => -2,
 * @return if new edges is added SUCCESS => 0
 */
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

/**
 * Removing edge from source to destination
 *
 * @param source 'from' part of the adding
 * @param destination 'to' part of the adding
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if destination is not exist DESTINATION_NODE_NOT_EXIST => -4,
 * @return if from source to destination is not real edge EDGE_NOT_EXIST => -5,
 * @return if edge is removed SUCCESS => 0
 */
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

/**
 * Checking edge is real edge from source to destination
 *
 * @param source 'from' part of the adding
 * @param destination 'to' part of the adding
 * @return if Graph hasn't any node, false,
 * @return if source is not exist, false,
 * @return if destination is not exist, false,
 * @return if edge is real edge true
 */
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

/**
 * Dijkstra Algorithm for finding shortest path weight
 *
 * @param graph Graph where the algorithm will be applied 
 * @param allDistances if algorithm succed, all finding distances added in this item
 * @param source 'from' part of the algorithm start
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if algorithm succed, SUCCESS => 0
 */
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

/**
 * Dijkstra Algorithm for finding shortest path weight
 *
 * @param graph Graph where the algorithm will be applied 
 * @param source 'from' part of the algorithm start
 * @return if Graph hasn't any node GRAPH_HAS_NOT_ANY_NODE => -1,
 * @return if source is not exist SOURCE_NODE_NOT_EXIST => -3,
 * @return if destination is not exist DESTINATION_NODE_NOT_EXIST => -4,
 * @return if algorithm succed shortest distance from source to destination
 */
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

/**
 * Helper and recursive function for checking acyclic graph
 * Reference: https://www.geeksforgeeks.org/detect-cycle-in-a-graph/
 *
 * @param visitingNode node is already visiting
 * @param visitedNode list of all visited nodes
 * @param recursiveStack is this node marked
 * @return if nodes generating a cycle, true
 * @return if nodes haven't cycle, false
 */
bool DirectedWeightedGraph::is_acyclicGraph(int visitingNode, bool visitedNode[], bool *recursiveStack)
{
    if (visitedNode[visitingNode] == false)
    {
        // Mark the current node as visited and part of recursion stack
        visitedNode[visitingNode] = true;
        recursiveStack[visitingNode] = true;

        // Recur for all the nodes adjacent to this node
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
    recursiveStack[visitingNode] = false; // remove the node from recursion stack
    return false;
}

/**
 * Checking graph has a cycle
 *
 * @return if graph has a cycle, true
 * @return if graph hasn't cycle, false
 */
bool DirectedWeightedGraph::is_acyclic(void)
{
    // Mark all the nodes as not visited and not part of recursion
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

/**
 * Printing graph elements as source, destination, weight
 *
 * @param graph is printing graph
 */
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