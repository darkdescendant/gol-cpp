cmake_minimum_required(VERSION 3.3)
project(GOLKata)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

add_subdirectory(GameOfLife)
add_subdirectory(TestApp)
add_subdirectory(App)
