project(tests)

add_subdirectory(../../gtest gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

set(SOURCE_FILES
        ../Strategy.cpp
        ../Strategies/Traitor.cpp
        ../Strategies/Loyal.cpp
        ../Controller.cpp
        ../ScoreMatrix.cpp
        ../Strategies/Random.cpp
        ../Strategies/Revengeful.cpp
        ../Strategies/Varying.cpp
        ../Arguments.cpp
        ../Strategies/Democracy.cpp
        ../ControllerFast.cpp
        ../ControllerDetailed.cpp
        ../ControllerTournament.cpp ../ControllerTournament.h ../Strategies/Fortress4.cpp ../Strategies/Fortress4.h ../Strategies/Sgs.cpp ../Strategies/Sgs.h)

add_executable(runTests
        FactoryTest.cpp
        GameTests.cpp
        ${SOURCE_FILES})

target_link_libraries(runTests gtest gtest_main)