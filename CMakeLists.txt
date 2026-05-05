cmake_minimum_required(VERSION 3.16)
project(MyFirstGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game src/main.cpp src/Player.cpp
        include/Asteroid.h)

target_link_libraries(game sfml-graphics sfml-window sfml-system)

target_include_directories(game PRIVATE include/)
