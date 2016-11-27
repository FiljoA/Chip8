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
	GUI/mainframe.h
)

add_executable(Chip8 ${SRCS})


set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 11)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/modules/")

find_package(SFML 2 REQUIRED COMPONENTS graphics window system)
if(SFML_FOUND)
	include_directories(${SFML_INCLUDE_DIR})
	target_link_libraries(Chip8 ${SFML_LIBRARIES})
else()
	message("SFML 2.X was not found")
endif()

find_package(Qt5Widgets)
if(Qt5Widgets_FOUND)
	message("-- Found Qt ${Qt5Widgets_VERSION}")
	include_directories(${Qt5Widgets_INCLUDE_DIRS})
	target_link_libraries(Chip8 ${Qt5Widgets_LIBRARIES})
else()
	message("Qt5 was not found")
endif()