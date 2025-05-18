cmake_minimum_required(VERSION 3.31)
project(Zavrsni_MravljiAlgGIT)



# Static linking for MinGW (GCC)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")


add_executable(Zavrsni_MravljiAlgoritamV2 sources/main.cpp sources/Graph.cpp
        sources/FormulaParsing.cpp
        sources/Ant.cpp
        sources/outputControll.cpp
        headers/outputControll.h)
