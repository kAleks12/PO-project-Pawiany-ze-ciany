cmake_minimum_required(VERSION 3.17)
project(PO)

set(CMAKE_CXX_STANDARD 20)
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/names.txt
        ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)
add_executable(PO main.cpp;Map.cpp Map.h Field.h Field.cpp Being.cpp Being.h Viking.cpp Viking.h Southern_Warrior.cpp Southern_Warrior.h Knight.cpp Knight.h Slav.cpp Slav.h Weapon.cpp Weapon.h Armor.cpp Armor.h)