cmake_minimum_required(VERSION 3.6)
project(prisoners)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
        main.cpp
        Factory.cpp
        Factory.h Strategy.cpp Strategy.h Strategies/Traitor.cpp Strategies/Traitor.h Strategies/Loyal.cpp Strategies/Loyal.h Controller.cpp Controller.h ScoreMatrix.cpp ScoreMatrix.h Strategies/Random.cpp Strategies/Random.h Strategies/Revengeful.cpp Strategies/Revengeful.h Strategies/Varying.cpp Strategies/Varying.h Arguments.cpp Arguments.h Strategies/Democracy.cpp Strategies/Democracy.h)
add_executable(prisoners ${SOURCE_FILES})