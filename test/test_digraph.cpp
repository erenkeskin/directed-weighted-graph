#include <gtest/gtest.h>
#include <climits>
#include "../include/dw_graph.h"

// Generate Test Fixture
class DiWeightedGraph : public testing::Test
{
public:
    void SetUp() override
    {
    }

    void TearDown() override
    {
    }
};

// Test for check graph get_nodeCount and set_nodeCount functions are okay
TEST_F(DiWeightedGraph, genereate_graph_check_getter_setter_node_count)
{
    DirectedWeightedGraph di_graph;
    ASSERT_EQ(di_graph.get_nodeCount(), -1);

    di_graph.set_nodeCount(5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);
}

// Test for check generating graph with predefined size
TEST_F(DiWeightedGraph, genereate_graph_with_constant_range)
{
    DirectedWeightedGraph di_graph(5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);
}

// Test for check generating graph with an item vector
// Item vector format => {source, destination, weight}
TEST_F(DiWeightedGraph, genereate_graph_with_items)
{
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3}};

    DirectedWeightedGraph di_graph(edges, 5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);
}

// Test for checking edge exist from source to destination
// If edge exist retval equal = SUCCESS => 0
// If edge source part not exist retval equal = SOURCE_NODE_NOT_EXIST => -3
// If edge destination part not exist retval equal = DESTINATION_NODE_NOT_EXIST => -4
// If checking edge from empty node retval equal = GRAPH_HAS_NOT_ANY_NODE => -1
TEST_F(DiWeightedGraph, existance_check)
{
    DirectedWeightedGraph di_graph(5);
    DirectedWeightedGraph di_graph_without_node_count;
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    di_graph.add_edge(0, 1, 3);
    di_graph.add_edge(0, 3, 7);
    di_graph.add_edge(0, 4, 8);
    di_graph.add_edge(1, 2, 1);
    di_graph.add_edge(1, 3, 4);
    di_graph.add_edge(3, 2, 2);
    di_graph.add_edge(4, 3, 3);

    int retval = di_graph.existance_check(0, 1);
    ASSERT_EQ(retval, SUCCESS);

    retval = di_graph.existance_check(5, 1);
    ASSERT_EQ(retval, SOURCE_NODE_NOT_EXIST);

    retval = di_graph.existance_check(1, 5);
    ASSERT_EQ(retval, DESTINATION_NODE_NOT_EXIST);

    retval = di_graph_without_node_count.existance_check(1, 5);
    ASSERT_EQ(retval, GRAPH_HAS_NOT_ANY_NODE);
}

// Test for checking edge exist for vector
// If edge exist retval equal = SUCCESS => 0
// If edge source part not exist retval equal = SOURCE_NODE_NOT_EXIST => -3
// If edge destination part not exist retval equal = DESTINATION_NODE_NOT_EXIST => -4
// If checking edge from empty node retval equal = GRAPH_HAS_NOT_ANY_NODE => -1
TEST_F(DiWeightedGraph, existance_check_for_vectors)
{
    vector<Edge> edges_source_not_exit = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {8, 2, 2},
        {3, 2, 2},
        {4, 3, 3}};

    vector<Edge> edges_destination_not_exit = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 7, 4},
        {1, 2, 2},
        {3, 2, 2},
        {4, 3, 3}};

    DirectedWeightedGraph di_graph_source_not_exist(edges_source_not_exit, 5);
    DirectedWeightedGraph di_graph_destination_not_exist(edges_destination_not_exit, 5);
    DirectedWeightedGraph di_graph_without_node_count;

    ASSERT_EQ(di_graph_source_not_exist.get_nodeCount(), 5);
    ASSERT_EQ(di_graph_source_not_exist.adjacencyList.size(), 5);
    ASSERT_EQ(di_graph_destination_not_exist.get_nodeCount(), 5);
    ASSERT_EQ(di_graph_destination_not_exist.adjacencyList.size(), 5);

    int retval = di_graph_source_not_exist.existance_check(edges_source_not_exit);
    ASSERT_EQ(retval, SOURCE_NODE_NOT_EXIST);

    retval = di_graph_destination_not_exist.existance_check(edges_destination_not_exit);
    ASSERT_EQ(retval, DESTINATION_NODE_NOT_EXIST);

    retval = di_graph_without_node_count.existance_check(edges_source_not_exit);
    ASSERT_EQ(retval, GRAPH_HAS_NOT_ANY_NODE);
    retval = di_graph_without_node_count.existance_check(edges_destination_not_exit);
    ASSERT_EQ(retval, GRAPH_HAS_NOT_ANY_NODE);
}

// Test for adding new edge to graph from source to destination
// add_edge(source, destination, weight)
TEST_F(DiWeightedGraph, add_edge_with_from_source_to_destination)
{
    DirectedWeightedGraph di_graph(5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int source = 1;
    int destination = 4;
    int weight = 6;
    int retval = di_graph.add_edge(source, destination, weight);
    ASSERT_EQ(retval, 0);
}

// Test for adding new edge to graph from source to destination with existance - already exist edge
TEST_F(DiWeightedGraph, add_edge_with_from_source_to_destination_existing_edge)
{
    DirectedWeightedGraph di_graph(5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int source = 1;
    int destination = 4;
    int weight = 6;
    int retval = di_graph.add_edge(source, destination, weight);
    ASSERT_EQ(retval, 0);

    retval = di_graph.add_edge(source, destination, weight);
    ASSERT_EQ(retval, ALREADY_EXIST);
}

// Test for adding new edge to graph from source to destination with existance - not exist edge
TEST_F(DiWeightedGraph, add_edge_with_from_source_to_destination_not_existing_node)
{
    DirectedWeightedGraph di_graph(5);
    int nodeCount = di_graph.get_nodeCount();

    ASSERT_EQ(nodeCount, 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int source = 6;
    int destination = 3;
    int weight = 6;

    int retval = di_graph.add_edge(source, destination, weight);
    ASSERT_EQ(retval, SOURCE_NODE_NOT_EXIST);

    source = 1;
    destination = 6;

    retval = di_graph.add_edge(source, destination, weight);
    ASSERT_EQ(retval, DESTINATION_NODE_NOT_EXIST);
}

// Test for adding new edge to graph with an vector
// Item vector format => {source, destination, weight}
TEST_F(DiWeightedGraph, add_edge_with_vector)
{
    DirectedWeightedGraph di_graph(5);
    int nodeCount = di_graph.get_nodeCount();

    ASSERT_EQ(nodeCount, 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3},
        {1, 2, 1}};

    int retval = di_graph.add_edge(edges);
    ASSERT_EQ(retval, ALREADY_EXIST);
}

// Test for checking edge is really edge
TEST_F(DiWeightedGraph, is_edge_from_source_to_destination)
{
    DirectedWeightedGraph di_graph(5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int source = 1;
    int destination = 4;
    int weight = 6;
    int retval = di_graph.add_edge(source, destination, weight);

    ASSERT_EQ(retval, 0);
    ASSERT_TRUE(di_graph.is_edge(source, destination));
    ASSERT_FALSE(di_graph.is_edge(source, 3));
}

// Test for checking edge is really edge - not existing node
TEST_F(DiWeightedGraph, is_edge_from_source_to_destination_not_existing_node)
{
    DirectedWeightedGraph di_graph(5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int retval = di_graph.add_edge(0, 1, 2);
    ASSERT_EQ(retval, SUCCESS);
    ASSERT_TRUE(di_graph.is_edge(0, 1));
    ASSERT_FALSE(di_graph.is_edge(0, 5));
}

// Test for remove edge from source to destination
TEST_F(DiWeightedGraph, remove_edge_from_source_to_destination)
{
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3}};

    DirectedWeightedGraph di_graph(edges, 5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int retval = di_graph.remove_edge(0, 1);
    ASSERT_EQ(retval, SUCCESS);
}

// Test for remove edge from source to destination - not existing node
TEST_F(DiWeightedGraph, remove_edge_from_source_to_destination_not_existing_node)
{
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3}};

    DirectedWeightedGraph di_graph(edges, 5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);

    int retval = di_graph.remove_edge(6, 1);
    ASSERT_EQ(retval, SOURCE_NODE_NOT_EXIST);

    retval = di_graph.remove_edge(0, 9);
    ASSERT_EQ(retval, DESTINATION_NODE_NOT_EXIST);
}

// Test for remove edge from source to destination - from not a real node
TEST_F(DiWeightedGraph, remove_edge_from_source_to_destination_not_edge)
{
    vector<Edge> edges = {
        {0, 1, 3},
        {0, 3, 7},
        {0, 4, 8},
        {1, 2, 1},
        {1, 3, 4},
        {3, 2, 2},
        {4, 3, 3}};

    DirectedWeightedGraph di_graph(edges, 5);
    ASSERT_EQ(di_graph.get_nodeCount(), 5);
    ASSERT_EQ(di_graph.adjacencyList.size(), 5);
    int retval = di_graph.remove_edge(0, 2);
    ASSERT_EQ(retval, EDGE_NOT_EXIST);
}

// Test for checking graph is acyclic
TEST_F(DiWeightedGraph, is_acyclic)
{
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

    ASSERT_EQ(not_acyclic_di_graph.get_nodeCount(), 5);
    ASSERT_EQ(not_acyclic_di_graph.adjacencyList.size(), 5);
    ASSERT_EQ(acyclic_di_graph.get_nodeCount(), 6);
    ASSERT_EQ(acyclic_di_graph.adjacencyList.size(), 6);

    ASSERT_FALSE(not_acyclic_di_graph.is_acyclic());
    ASSERT_TRUE(acyclic_di_graph.is_acyclic());
}

// Test for checking graph shortest path with Dijkstra Algorithm from source to destination
// Parameters: {graph, source, destination}
// If edge source part not exist retval equal = SOURCE_NODE_NOT_EXIST => -3
// If edge destination part not exist retval equal = DESTINATION_NODE_NOT_EXIST => -4
// If checking edge from empty node retval equal = GRAPH_HAS_NOT_ANY_NODE => -1
// If parameters okay, retval equal shortest path weight from source to destination
// If shortest path is not exist from source to destination, retval equal = INT_MAX
TEST_F(DiWeightedGraph, dijkstra_from_source_to_destination)
{
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
    DirectedWeightedGraph di_graph(edges, 6);
    DirectedWeightedGraph di_graph_without_node_count;

    ASSERT_EQ(di_graph.get_nodeCount(), 6);
    ASSERT_EQ(di_graph.adjacencyList.size(), 6);

    int retval = dijkstra(di_graph_without_node_count, 6, 0);
    ASSERT_EQ(retval, GRAPH_HAS_NOT_ANY_NODE);

    retval = dijkstra(di_graph, 6, 0);
    ASSERT_EQ(retval, SOURCE_NODE_NOT_EXIST);

    retval = dijkstra(di_graph, 0, 6);
    ASSERT_EQ(retval, DESTINATION_NODE_NOT_EXIST);

    retval = dijkstra(di_graph, 0, 2);
    ASSERT_EQ(retval, 3);

    retval = dijkstra(di_graph, 1, 0);
    ASSERT_EQ(retval, 8);

    retval = dijkstra(di_graph, 5, 0);
    ASSERT_EQ(retval, INT_MAX);
}

// Test for checking graph shortest path with Dijkstra Algorithm from source to all nodes
// Parameters: {graph, shortest_distances, source}
// If checking edge from empty node retval equal = GRAPH_HAS_NOT_ANY_NODE => -1
TEST_F(DiWeightedGraph, dijkstra_from_source_to_all_nodes)
{
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
    DirectedWeightedGraph di_graph(edges, 6);
    DirectedWeightedGraph di_graph_without_node_count;

    ASSERT_EQ(di_graph.get_nodeCount(), 6);
    ASSERT_EQ(di_graph.adjacencyList.size(), 6);

    vector<int> allDistances;
    vector<int> checkAllDistancesForZero = {
        0, 4, 3, 6, 8, 14};
    vector<int> checkAllDistancesForOne = {
        8, 0, 5, 2, 4, 10};
    vector<int> checkAllDistancesForFive = {
        INT_MAX, INT_MAX, INT_MAX, INT_MAX, INT_MAX, 0};

    int retval = dijkstra(di_graph_without_node_count, allDistances, 0);
    ASSERT_EQ(retval, GRAPH_HAS_NOT_ANY_NODE);

    //
    dijkstra(di_graph, allDistances, 0);
    for (int i = 0; i < allDistances.size(); i++)
    {
        ASSERT_EQ(allDistances.at(i), checkAllDistancesForZero.at(i));
    }

    //
    dijkstra(di_graph, allDistances, 1);
    for (int i = 0; i < allDistances.size(); i++)
    {
        ASSERT_EQ(allDistances.at(i), checkAllDistancesForOne.at(i));
    }

    //
    dijkstra(di_graph, allDistances, 5);
    for (int i = 0; i < allDistances.size(); i++)
    {
        ASSERT_EQ(allDistances.at(i), checkAllDistancesForFive.at(i));
    }
}