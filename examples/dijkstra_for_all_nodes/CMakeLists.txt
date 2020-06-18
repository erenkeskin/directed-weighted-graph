include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(dijkstra_for_all_nodes dijkstra_for_all_nodes.cpp)

target_link_libraries(
    dijkstra_for_all_nodes
    dw_graph
)