#include "../include/dw_graph.h"
#include <iostream>

// Driver program to methods of graph class
int main(int argc, char **argv)
{
    // Generating Graph with size 5
    vector<Edge> not_acyclic = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3}};

    vector<Edge> acyclic = {
        {0, 1, 4},
        {1, 3, 4},
        {2, 1, 3},
        {3, 2, 2},
        {3, 1, 3},
        {3, 4, 3},
        {4, 3, 5},
        {4, 5, 1},
        {4, 1, 4},
        {5, 0, 5},
    };

    DirectedWeightedGraph not_acyclic_di_graph(not_acyclic, 5);
    DirectedWeightedGraph acyclic_di_graph(acyclic, 6);

    //
    if (acyclic_di_graph.is_acyclic())
    {
        cout << "Graph is acyclic";
    }
    else
    {
        cout << "Graph is not acyclic";
    }

    //
    if (not_acyclic_di_graph.is_acyclic())
    {
        cout << "Graph is acyclic";
    }
    else
    {
        cout << "Graph is not acyclic";
    }

    return 0;
}