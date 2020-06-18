add_library(acylic_graph ${PROJECT_SOURCE_DIR}/examples/acylic_graph/acylic_graph.cpp)
include_directories("${PROJECT_SOURCE_DIR}/include")

add_executable(acylic_graph acylic_graph.cpp)

target_link_libraries(
    acylic_graph
)