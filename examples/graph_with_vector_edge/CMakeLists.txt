include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(graph_with_vector_edge graph_with_vector_edge.cpp)

target_link_libraries(
    graph_with_vector_edge
    dw_graph
)