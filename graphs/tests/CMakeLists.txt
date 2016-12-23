project(tests)

add_subdirectory(../../gtest gtest)

include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")

add_definitions(--coverage)
set(CMAKE_EXE_LINKER_FLAGS ${CMAKE_EXE_LINKER_FLAGS} " --coverage")

add_executable(runTests
        GraphTest.cpp
        )

target_link_libraries(runTests gtest gtest_main)