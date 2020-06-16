#include <iostream>
#include <vector>
#include "dw_graph.h"

using namespace std;

void printGraph(DirectedWeightedGraph &graph)
{
    for (int i = 0; i < graph.get_nodeCount(); i++)
    {
        /*Here, we print all the neighboring vertices and their weights 
        of given source vertex*/
        cout << "Source: " << i << " -> ";
        for (auto p : graph.adjacencyList[i])
        {
            cout << "(Dest: " << p.first << ", Weight: " << p.second << ") ";
        }
        cout << endl;
    }
}

// Driver program to test methods of graph class
int main()
{
    // Create a graph given in the above diagram
    int nodeCount = 5;

    vector<int> nodes = {0, 1, 2, 3, 4};

    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3}};

    vector<Edge> edges2 = {
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

    DirectedWeightedGraph di_graph(edges, nodeCount);

    // di_graph.add_edge(2, 4, 6);

    // printGraph(di_graph);
    // cout << "--------------------------------------" << endl;
    // cout << "--------------------------------------" << endl;

    // DirectedWeightedGraph di_graph2(nodeCount);

    // di_graph2.add_edge(1, 4, 6);
    // di_graph2.add_edge(2, 3, 6);
    // di_graph2.add_edge(3, 2, 6);
    // di_graph2.add_edge(4, 1, 6);

    // printGraph(di_graph2);
    // cout << "--------------------------------------" << endl;
    // cout << "--------------------------------------" << endl;

    // DirectedWeightedGraph di_graph3;
    // di_graph3.set_nodeCount(nodeCount);
    // di_graph3.add_edge(0, 1, 2);
    // di_graph3.add_edge(0, 2, 3);
    // di_graph3.add_edge(edges);

    // printGraph(di_graph3);
    // cout << "--------------------------------------" << endl;
    // cout << "--------------------------------------" << endl;

    // di_graph.remove_edge(1, 2);
    // printGraph(di_graph);
    // cout << "--------------------------------------" << endl;
    // cout << "--------------------------------------" << endl;

    vector<int> allDistances;
    
    int source = 0;
    dijkstra(di_graph, allDistances, source);

    cout << "Minimum distances from vertex: " << source << endl;
    for (int i = 0; i < nodeCount; i++)
    {
        if (allDistances[i] < INT_MAX)
        {
            cout << "Vertex: " << i << "\tDistance: " << allDistances[i] << endl;
        }
    }

    // -------------------------------------------------
    // -------------------------------------------------
    // -------------------------------------------------
    // -------------------------------------------------
    // -------------------------------------------------

    // Vertex vertexes(vertexCount);

    // vertexes.add_vertex(0, 1, 3);
    // vertexes.add_vertex(0, 3, 7);
    // vertexes.add_vertex(0, 4, 8);
    // vertexes.add_vertex(1, 2, 1);
    // vertexes.add_vertex(1, 3, 4);
    // vertexes.add_vertex(3, 2, 2);
    // vertexes.add_vertex(4, 3, 3);

    // DirectedWeightedGraph di_graph(&vertexes);

    // di_graph.printGraph();

    // Edges edges[] = {
    //     // (x, y, w) -> edge from x to y with weight w
    //     {0, 1, 3},
    //     {0, 3, 7},
    //     {0, 4, 8},
    //     {1, 2, 1},
    //     {1, 3, 4},
    //     {3, 2, 2},
    //     {4, 3, 3}};
    // Create a graph given in the above diagram

    return 0;
}