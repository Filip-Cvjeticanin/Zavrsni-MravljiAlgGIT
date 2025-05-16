cmake_minimum_required(VERSION 3.31)
project(Zavrsni_MravljiAlgoritamV2)

set(CMAKE_CXX_STANDARD 20)

add_executable(Zavrsni_MravljiAlgoritamV2 sources/main.cpp sources/Graph.cpp
        sources/FormulaParsing.cpp
        sources/Ant.cpp)
