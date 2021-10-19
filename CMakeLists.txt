cmake_minimum_required(VERSION 3.1)
project(HashProgram)
set(CMAKE_CXX_STANDARD 17)
ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/3rdparty/gtest)

# Boost #
find_package(Boost 1.77.0 COMPONENTS program_options filesystem thread fiber REQUIRED)

# С Flags #
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1z -Wall -Wreturn-type")

include_directories(src)

add_subdirectory(src)
if (CMAKE_BUILD_TYPE MATCHES Testing)
    enable_testing()
    add_subdirectory(tests)
    add_test(NAME HashProgramTestt COMMAND HashProgramTest)
endif ()