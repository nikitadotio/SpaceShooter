cmake_minimum_required(VERSION 3.16)
project(MyFirstGame)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(game src/main.cpp src/Player.cpp
        include/Asteroid.h
        src/Asteroid.cpp)

target_link_libraries(game sfml-graphics sfml-window sfml-system)

target_include_directories(game PRIVATE include/)

add_custom_command(TARGET game POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/assets"
        "$<TARGET_FILE_DIR:game>/assets"
)
