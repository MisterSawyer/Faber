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

add_subdirectory(sources)
