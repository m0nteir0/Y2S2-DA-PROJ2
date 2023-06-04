cmake_minimum_required(VERSION 3.23)
project(DA_PROJECT2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DA_PROJECT2 main.cpp src/algorithms/Interface.cpp src/algorithms/Data.cpp "src/dataStructures/Graph.cpp" "src/dataStructures/VertexEdge.cpp")
