add_library(graph_with_vector_edge ${PROJECT_SOURCE_DIR}/examples/graph_with_vector_edge/graph_with_vector_edge.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(graph_with_vector_edge graph_with_vector_edge.cpp)

target_link_libraries(
    graph_with_vector_edge
)