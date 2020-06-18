# CMake required
cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# Project Name
project(DirectedWeightedGraph)

# Project Setup
set(CMAKE_CXX_STANDARD 14)
if(CMAKE_COMPILER_IS_GNUCXX)
    add_definitions(-std=gnu++0x)
endif()

enable_testing()

set(PROJECT_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include)
set(PROJECT_SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(PROJECT_TEST_DIR ${PROJECT_SOURCE_DIR}/test)
set(PROJECT_EXAMPLE_DIR ${PROJECT_SOURCE_DIR}/examples)

include_directories(${PROJECT_INCLUDE_DIR})
 
#Bring the headers, such as Student.h into the project
include_directories(include)
  
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(main ${SOURCES})