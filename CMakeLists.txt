cmake_minimum_required(VERSION 3.23)
project(DA_PROJECT2)

set(CMAKE_CXX_STANDARD 11)

add_executable(DA_PROJECT2 main.cpp algorithms/Interface.cpp algorithms/Data.cpp "dataStructures/Graph.cpp" "dataStructures/VertexEdge.cpp")
