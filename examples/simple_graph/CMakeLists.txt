add_library(simple_graph ${PROJECT_SOURCE_DIR}/examples/simple_graph/simple_graph.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(simple_graph simple_graph.cpp)

target_link_libraries(
    simple_graph
)