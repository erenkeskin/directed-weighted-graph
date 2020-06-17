set(TARGET PROJECT_SOURCES)

set(HEADER_FILE
    ${PROJECT_INCLUDE_DIR}/dw_graph.h
)

set(PROJECT_SOURCE_FILES
    ${PROJECT_SRC_DIR}/main.cpp
    ${PROJECT_SRC_DIR}/dw_graph.cpp
)

add_library(${TARGET}
    ${PROJECT_SOURCE_FILES}
    ${HEADER_FILE}
)

add_executable(main main.cpp)