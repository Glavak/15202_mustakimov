cmake_minimum_required(VERSION 3.6)
project(myArray)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w3")

set(SOURCE_FILES
        main.cpp
        Searches.h GraphLinked.h)

add_executable(run ${SOURCE_FILES})

add_subdirectory(tests)