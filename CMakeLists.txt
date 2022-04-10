cmake_minimum_required(VERSION 3.21)
project(Pong)

set(CMAKE_CXX_STANDARD 14)

set(SFML_INCLUDE_DIR C:/Dev/lib/SFML/include)
set(SFML_LIB_DIR C:/Dev/lib/SFML/lib)

include_directories(${SFML_INCLUDE_DIR})
link_directories(${SFML_LIB_DIR})

add_executable(Pong main.cpp Pong.cpp Pong.h)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)
