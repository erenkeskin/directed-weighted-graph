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

public:
    vector<vector<pair<int, int>>> adjacencyList;
    
    DirectedWeightedGraph();
    DirectedWeightedGraph(int nodeCount);
    DirectedWeightedGraph(vector<Edge> &edges, int nodeCount);

    void set_nodeCount(int nodeCount) { totalNodeCount = nodeCount; };
    int get_nodeCount(void) { return totalNodeCount; };

    void add_edge(int source, int destination, int weight);
    void add_edge(vector<Edge> &edges);

    void printGraph();
    ~DirectedWeightedGraph();
};

#endif // _DW_GRAPH_H