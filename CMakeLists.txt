cmake_minimum_required (VERSION 3.22.1)

project(Tetris_C++)

find_package(SFML REQUIRED)

add_executable(${PROJECT_NAME} main.cpp)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
target_link_libraries(${PROJECT_NAME} sfml-audio)

