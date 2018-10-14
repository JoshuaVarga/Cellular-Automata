cmake_minimum_required(VERSION 3.1)

project(Cellular-Automata)

#Add files
file(GLOB_RECURSE SOURCES
    "Source/*.cpp"
    "Source/*.h"
)

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Debug)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/Release)

configure_file(Source/arial.ttf ${CMAKE_BINARY_DIR} COPYONLY)
configure_file(Source/arial.ttf ${CMAKE_BINARY_DIR}/Debug COPYONLY)
configure_file(Source/arial.ttf ${CMAKE_BINARY_DIR}/Release COPYONLY)

set(SFML_BIN_DIR "SFML_BIN_DIR-NOTFOUND" CACHE PATH "")


if (SFML_BIN_DIR)
	file(GLOB_RECURSE ASSETS "${SFML_BIN_DIR}/*")

	file(COPY ${ASSETS} DESTINATION "${CMAKE_BINARY_DIR}/Debug/")
	file(COPY ${ASSETS} DESTINATION "${CMAKE_BINARY_DIR}/Release/")
endif()

#Define the executable
add_executable(
	${PROJECT_NAME} 
	${SOURCES}
)

#Add SFML
find_package(SFML 2.5 COMPONENTS graphics REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics)