cmake_minimum_required(VERSION 3.17)
project(PO)

set(CMAKE_CXX_STANDARD 20)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/names.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
SET(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} " -g")
add_executable(PO main.cpp;Terrain/Map.cpp Terrain/Map.h Terrain/Field.h Terrain/Field.cpp Troops/Being.cpp Troops/Being.h Troops/Viking.cpp Troops/Viking.h Troops/Nomad.cpp Troops/Nomad.h Troops/Knight.cpp Troops/Knight.h Troops/Slav.cpp Troops/Slav.h Items/Item.cpp Items/Item.h)