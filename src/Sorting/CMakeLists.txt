cmake_minimum_required (VERSION 2.8.11)
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

if ( "${CMAKE_BUILD_TYPE}" STREQUAL "Debug" )
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O0")
	message("Added debug flags")
endif()

file(GLOB SOURCES *.cpp)
#find_package( Boost REQUIRED COMPONENTS program_options regex )
#include_directories( ${Boost_INCLUDE_DIRS} )
# Alternatively you could use ${Boost_LIBRARIES} here.
add_executable(sorting_algs ${SOURCES})
#target_link_libraries( sorting_algs ${Boost_PROGRAM_OPTIONS_LIBRARY} ${Boost_REGEX_LIBRARY} )
