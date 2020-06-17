#include "../include/dw_graph.h"

// Driver program to methods of graph class
int main(int argc, char **argv)
{    
    DirectedWeightedGraph di_graph(5);

    di_graph.add_edge(0, 1, 2);
    di_graph.add_edge(1, 2, 3);
    di_graph.add_edge(2, 3, 4);
    di_graph.add_edge(3, 4, 5);
    di_graph.add_edge(4, 5, 6);

    printGraph(di_graph);

    return 0;
}