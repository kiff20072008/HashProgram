cmake_minimum_required(VERSION 3.1)

include_directories(${CMAKE_SOURCE_DIR}/src/)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})


set(SOURCES "${PROJECT_SOURCE_DIR}/src/HashCreator.cpp" "${PROJECT_SOURCE_DIR}/src/HashCreator.hpp"
        "${PROJECT_SOURCE_DIR}/src/FileHandler.cpp" "${PROJECT_SOURCE_DIR}/src/FileHandler.hpp"
        "${PROJECT_SOURCE_DIR}/src/Logger.hpp" "${PROJECT_SOURCE_DIR}/src/strConstants.hpp"
        "${PROJECT_SOURCE_DIR}/src/constants.hpp" ../src/Logger.cpp)

project(HashProgramTest)

set(UNIT_TEST_SOURCES tests.cpp)
set(TEST_BIN_NAME HashProgramTest)

add_executable(${TEST_BIN_NAME} ${UNIT_TEST_SOURCES} ${SOURCES})
target_link_libraries(${TEST_BIN_NAME} LINK_PUBLIC gtest gtest_main ${Boost_LIBRARIES})