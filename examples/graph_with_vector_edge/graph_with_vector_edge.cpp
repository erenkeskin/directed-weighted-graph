#include "../include/dw_graph.h"

// Driver program to methods of graph class
int main(int argc, char **argv)
{    
    // Generating Graph with size 5
    DirectedWeightedGraph di_graph(5);

    // Adding New Edges to Graph with vectors
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3},
        {1, 2, 1}};

    di_graph.add_edge(edges);

    // Printing Graph
    printGraph(di_graph);

    return 0;
}