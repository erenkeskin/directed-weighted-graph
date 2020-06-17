#ifndef _DW_GRAPH_H
#define _DW_GRAPH_H

#include <vector>

using namespace std;

// Return codes for all functions
enum RETURN_CODES
{
    SUCCESS = 0,
    GRAPH_HAS_NOT_ANY_NODE = -1,
    ALREADY_EXIST = -2,
    SOURCE_NODE_NOT_EXIST = -3,
    DESTINATION_NODE_NOT_EXIST = -4,
    EDGE_NOT_EXIST = -5
};

// Edge structure which is store source, destination and weight of any node
struct Edge
{
    int source;
    int destination;
    int weight;
};

// Directed Weighted Graph Class
class DirectedWeightedGraph
{
private:
    int totalNodeCount = -1;
    bool visited = false;
    bool is_acyclicGraph(int visitingNode, bool visitedNode[], bool *recursiveStack); // used in isCyclic() function

public:
    vector<vector<pair<int, int>>> adjacencyList; // List of all nodes and connections

    // Constructor
    DirectedWeightedGraph();
    DirectedWeightedGraph(int nodeCount);
    DirectedWeightedGraph(vector<Edge> &edges, int nodeCount);

    // Destructor
    ~DirectedWeightedGraph();

    void set_nodeCount(int nodeCount);
    int get_nodeCount(void);

    int existance_check(int source, int destination);
    int existance_check(vector<Edge> &edges);

    int add_node();
    int remove_node();

    int add_edge(int source, int destination, int weight);
    int add_edge(vector<Edge> &edges);

    int remove_edge(int source, int destination);

    bool is_edge(int source, int destination);
    bool is_acyclic(void); // returns true if there is a cycle in this graph

    friend void printGraph(DirectedWeightedGraph graph);

    friend int dijkstra(DirectedWeightedGraph graph, vector<int> &allDistances, int source);
    friend int dijkstra(DirectedWeightedGraph graph, int source, int destination);
};

#endif // _DW_GRAPH_H