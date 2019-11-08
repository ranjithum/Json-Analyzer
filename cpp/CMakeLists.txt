cmake_minimum_required(VERSION 3.10.2)

project(json_analyzer VERSION 1.0 LANGUAGES CXX)
 
find_package(BISON)
find_package(FLEX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(.)
include_directories(third_party/rapidjson/include)

option(BuildLibrary "Build the library by default" ON)
option(BuildTest "Build the unit tests." OFF)
option(BuildGcov "Build test suite with coverage information" OFF)

# Uncomment below for debugging parser
# add_definitions(-DYYDEBUG=1)

set (CMAKE_CXX_FLAGS "-fPIC -Wall -g -Wno-write-strings -Wno-sign-compare -Wno-unused-function")

set(OBJECT_DIR ${CMAKE_BINARY_DIR}/CMakeFiles/json_analyzer.dir/src)

if (BuildGcov AND BuildTest)
	message("---- Building test suite with coverage information -----")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -fprofile-arcs -ftest-coverage")
	set(CMAKE_CXX_OUTPUT_EXTENSION_REPLACE ON)
	add_custom_target(gcov
		COMMAND ${CMAKE_MAKE_PROGRAM} test
		COMMAND gcov -a ${CMAKE_SOURCE_DIR}/src/*.cpp -o ${OBJECT_DIR}
		COMMAND lcov --capture --directory ${CMAKE_BINARY_DIR} --output-file main_coverage.info
		COMMAND lcov --remove main_coverage.info --output-file main_coverage.filter '/usr/include/*'
		'${CMAKE_SOURCE_DIR}/third_party/rapidjson/*' '${CMAKE_SOURCE_DIR}/third_party/doctest/*' '${CMAKE_SOURCE_DIR}/test/*'
		COMMAND genhtml main_coverage.filter --output-directory /www/data/gcov
		WORKING_DIRECTORY ${CMAKE_BINARY_DIR}  # Need separate command for this line
		COMMAND echo "Coverage report captured at /www/data/gcov.. Use any lighweight http server to see the results"
		)
endif()

BISON_TARGET(parser src/json_analyzer.ypp ${CMAKE_CURRENT_BINARY_DIR}/json_analyzer.tab.cpp)
FLEX_TARGET(scanner src/json_analyzer.l ${CMAKE_CURRENT_BINARY_DIR}/json_analyzer.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(scanner parser)
include_directories(${CMAKE_CURRENT_BINARY_DIR})

file(GLOB SOURCES "src/*.cpp")

#Generate the shared library from the sources
add_library(json_analyzer SHARED ${SOURCES} ${BISON_parser_OUTPUTS} ${FLEX_scanner_OUTPUTS})

include(CTest) #adds option BUILD_TESTING
if(BUILD_TESTING AND BuildTest)
    enable_testing()
    add_subdirectory(test)
endif()
