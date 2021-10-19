cmake_minimum_required(VERSION 3.1)
project(HashProgram)

set(PROJECT_SOURCES HashCreator.cpp HashCreator.hpp Logger.hpp FileHandler.cpp FileHandler.hpp strConstants.hpp Logger.cpp)

add_executable(HashProgram main.cpp ${PROJECT_SOURCES})
target_link_libraries(HashProgram LINK_PUBLIC ${Boost_LIBRARIES})