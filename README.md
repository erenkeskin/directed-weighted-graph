Directed and Weighted Graph implementation with C++, checking acyclic graph and finding shortest path weight with Dijkstra Algoritm. All functions are already tested.

## Build

```bash
git clone https://github.com/erenkeskin/directed-weighted-graph.git
mkdir build
cd build
cmake ..
make
```
## Run Tests
~~~
cd build && ./test/test_main
~~~

## Run Main
~~~
cd build && ./main
~~~

## File Structure

    ├── directed-weighted-graph         # main folder of project
        ├── include
        │   └── dw_graph.h              # Directed Weight Graph Header File              
        ├── src
        │   ├── CMakeList.txt           # CMake defination for the whole src folder
        │   └── main.cpp                # Main entrance
        │   └── dw_graph.cpp            # Directed Weight Graph Implementation
        ├── test                
        │   └── CMakeLists.txt          # CMake defination for the whole test folder
        │   │   main.cpp                # Entrance of this test case
        │   │   test_digraph.cpp        # Test case declaration file 
        └── CMakeLists.txt

## Directed Weighted Graph Defination
Graph notation that is used to represent the connection between pairs of objects. It consists of:
    A set of nodes, which are also known as nodes. It represents like N.
    A set of edges, which are the links that connect the nodes. It represents like E.
Also graphs has to general type:
    Directed Graph: Which edges has a direction to connect to another node
    Undirected Graph: Which all graph connected to each other without any direction. It is like bi-directional graph
In this repository, our goal is to implement an simple directed graph with weighted edges. Weight is the distance between two connected nodes.
There is two main methods for representing Directed Weighted Graphs:
    Adjacency Matrix: generating graph to help with two-dimensional array. Memory Usage: O(n^2)
    Adjacency List: generating graph to help with an array of lists. Size is equal to total node size. Memory Usage: O(n+e)
I choose "Adjacency List" method for implementing for this repository.

Path = a sequence "n1, n2, ... nN" such that (ni, ni+1) is in E for i = 1,2,...,N-1
In a Directed Graph
    Cycle = a path of length at least 1 such that n1 = nN
    Simple Cycle = simple path that is also a cycle
Directed Acyclic Graph (DAG) = A directed graph with no cycles.

## Dijkstra Algorithm
Dijkstra Algorithm is an algorithm to find shortest path in a graph from source node to all other nodes or wanted node. In the running algorithm first generating an array which all elements representing like a big number or infinity (INF). After that algorithm running from source node to other connected nodes and update the generared array with distance between nodes. Running with updating all nodes but if there is an connected nodes the weight of the edges are adding each other. We can find shorthest path weight to help with Dijkstra algorithm.
Unfortunately, the algorithm does not work successfully if there is an edge with a negative (-) value. This is because the edge in the minus (-) value constantly produces a better result than the current situation, and the algorithm has never been stable.

## Examples
simple_graph
graph_with_vector_edge
dijkstra_simple_graph
dijkstra_for_all_nodes
acylic_graph

## References
img-1 https://www.grasshopper3d.com/forum/topics/adjacency-matrix-to-a-weighted-directed-graph
img-2 https://algorithms.tutorialhorizon.com/weighted-graph-implementation-java/
GoogleTest for CMake : https://github.com/YouYue123/GoogleTest-With-CMake
Description https://study.com/academy/lesson/weighted-graphs-implementation-dijkstra-algorithm.html
https://people.eecs.berkeley.edu/~nirkhe/cs38notes/graph.pdf
https://condor.depaul.edu/glancast/393class/docs/lecMay25.html