cmake_minimum_required(VERSION 3.24.1)

project(Cellular-Automata)

set(SFML_STATIC_LIBRARIES TRUE)

file(GLOB_RECURSE SOURCES
    "src/*.cpp"
    "src/*.h"
)

configure_file(src/arial.ttf ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)

add_executable(${PROJECT_NAME}  ${SOURCES})

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics)