set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

cmake_minimum_required (VERSION 3.5)
project(FaberFramework 
	VERSION 1.0.0
	DESCRIPTION "C++ app/game engine"
	LANGUAGES CXX)

# use ccache if available
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    message(STATUS "Found ccache in ${CCACHE_PROGRAM}")
    set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${CCACHE_PROGRAM}")
endif()

# include the configuration file
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Config.cmake)

set(ADDITIONAL_LIBS "${CMAKE_CURRENT_SOURCE_DIR}/libs")
add_subdirectory(sources)
