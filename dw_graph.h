#ifndef _DW_GRAPH_H
#define _DW_GRAPH_H

#include <vector>

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

public:
    vector<vector<pair<int, int>>> adjacencyList;

    DirectedWeightedGraph();
    DirectedWeightedGraph(int nodeCount);
    DirectedWeightedGraph(vector<Edge> &edges, int nodeCount);

    void set_nodeCount(int nodeCount) { totalNodeCount = nodeCount; };
    int get_nodeCount(void) { return totalNodeCount; };

    int add_edge(int source, int destination, int weight);
    int add_edge(vector<Edge> &edges);

    int remove_edge(int source, int destination);

    bool is_edge(int source, int destination);

    int dijkstra(int source, int destination);
    int dijkstra(int destination);

    void printGraph();
    ~DirectedWeightedGraph();
};

#endif // _DW_GRAPH_H