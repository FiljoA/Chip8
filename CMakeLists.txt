cmake_minimum_required(VERSION 3.1)

project(Chip8)

set(VERSION_MAJOR 0)
set(VERSION_MINOR 1)
set(VERSION_PATCH 0)

configure_file (
	"${PROJECT_SOURCE_DIR}/config.h.in"
	"${PROJECT_BINARY_DIR}/config.h"
)

include_directories("${PROJECT_BINARY_DIR}")

set(SRCS
	main.cpp
	Chip8.cpp
	Graphics.cpp
)

set(CMAKE_CXX_STANDARD 11)
add_definitions(-DDEBUG_INS)

add_executable(Chip8 ${SRCS})


set(CMAKE_AUTOMOC ON)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")

if(WIN32)
	set(SFML_STATIC_LIBRARIES TRUE)
endif()

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	if(WIN32)
		target_link_libraries(Chip8 ${SFML_DEPENDENCIES})
	endif()
	target_link_libraries(Chip8 ${SFML_LIBRARIES})
else()
	message("SFML 2.X was not found")
endif()