#ifndef _DW_GRAPH_H
#define _DW_GRAPH_H

#include <vector>
#include <climits>

using namespace std;

struct Edge
{
    int source;
    int destination;
    int weight;
};

class DirectedWeightedEdge
{

public:
    DirectedWeightedEdge();
    ~DirectedWeightedEdge();
};

class DirectedWeightedGraph
{
private:
    int totalNodeCount;
    bool visited = false;
    bool marked = false;
    bool is_acyclicGraph(int visitingNode, bool visitedNode[], bool *recursiveStack);  // used by isCyclic() 

public:
    vector<vector<pair<int, int>>> adjacencyList;

    DirectedWeightedGraph();
    DirectedWeightedGraph(int nodeCount);
    DirectedWeightedGraph(vector<Edge> &edges, int nodeCount);

    void set_nodeCount(int nodeCount) { totalNodeCount = nodeCount; };
    int get_nodeCount(void) { return totalNodeCount; };

    int add_node();
    int remove_node();

    int add_edge(int source, int destination, int weight);
    int add_edge(vector<Edge> &edges);

    int remove_edge(int source, int destination);

    bool is_edge(int source, int destination);
    bool is_acyclic(void);    // returns true if there is a cycle in this graph 

    void printGraph();

    friend void dijkstra(DirectedWeightedGraph graph, vector<int> & allDistances, int source);
    friend int dijkstra(DirectedWeightedGraph graph, int source, int destination);
    
    ~DirectedWeightedGraph();
};

#endif // _DW_GRAPH_H