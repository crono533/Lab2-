
cmake_minimum_required(VERSION 3.10)


project(AllocatorIntegrationConsoleApp VERSION 1.0 LANGUAGES CXX)


file(GLOB SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*.h") 



add_library(Allocator STATIC ${SOURCES})


target_include_directories(Allocator PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


# add_executable(AllocatorApp ${SOURCES})



