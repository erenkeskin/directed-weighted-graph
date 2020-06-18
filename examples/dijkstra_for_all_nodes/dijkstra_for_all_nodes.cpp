#include "../include/dw_graph.h"
#include <iostream>

// Driver program to methods of graph class
int main(int argc, char **argv)
{
    // Adding New Edges to Graph
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 3},
        {1, 2, 5},
        {1, 3, 2},
        {2, 3, 7},
        {3, 4, 2},
        {4, 5, 6},
        {4, 1, 4},
        {4, 0, 4}};
        
    // Generating Graph with size 6
    DirectedWeightedGraph di_graph(edges, 6);

    vector<int> allDistances;

    //
    dijkstra(di_graph, allDistances, 0);
    for (int i = 0; i < allDistances.size(); i++)
    {
        cout << "Shortest Path Weight from " << 0 << " to " << i << ": ";
        cout << allDistances.at(i) << endl;
    }

    return 0;
}