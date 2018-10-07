cmake_minimum_required(VERSION 2.8.11)
project (Algorithms)

set (CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
	message("Added debug flags")
endif()


add_subdirectory(src)
