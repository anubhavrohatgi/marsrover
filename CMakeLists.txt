#cmake for Clustering Project
set(PROJECT_NAME MarsRovers)
project(${PROJECT_NAME})

#Minimum version of Cmake required
cmake_minimum_required(VERSION 3.5)

IF(NOT CMAKE_BUILD_TYPE)
	set(CMAKE_BUILD_TYPE Release)
ENDIF(NOT CMAKE_BUILD_TYPE)


# place binaries and libraries according to GNU standards
include(GNUInstallDirs)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR})


# Options. Turn on with 'cmake -D<varname>=ON'.
option(TEST "Build all tests." OFF)

#Check for C++ Compiler version. I am using C++11.
INCLUDE(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

IF(COMPILER_SUPPORTS_CXX11)
    SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
ELSE()
    MESSAGE(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
ENDIF()


# we use this to get code coverage
if(CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs -ftest-coverage")
endif()


set(COMMON_INCLUDES ${PROJECT_SOURCE_DIR}/include)

#include the header files located in the include folder
include_directories(include)

#Set the variables for Headers and Sources. Manually add the filenames. This 
#is useful if the files are changed, removed or name modified.
#Better than GLOB version
set( 	HEADERS
	include/common.h
	include/fileio.h
	include/rover.h
	include/terrain.h
)

set( 	SOURCES
	src/terrain.cpp
	src/rover.cpp
	src/fileio.cpp	
	src/main.cpp
)

add_library(marsroverlib 
	src/terrain.cpp
	src/rover.cpp
	src/fileio.cpp)

add_executable(marsrover ${SOURCES} ${HEADERS})
target_link_libraries(marsrover marsroverlib)

if (TEST)  

	include(cmake/googletest.cmake)
	fetch_googletest(
	    ${PROJECT_SOURCE_DIR}/cmake
	    ${PROJECT_BINARY_DIR}/googletest
	)
	
        enable_testing()
  	        
	include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

        add_executable(runtests test/testing.cpp)


        target_link_libraries(runtests gtest gtest_main)


        target_link_libraries(runtests marsroverlib)
endif()



