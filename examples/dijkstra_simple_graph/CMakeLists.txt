include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(dijkstra_simple_graph dijkstra_simple_graph.cpp)

target_link_libraries(
    dijkstra_simple_graph
    dw_graph
)