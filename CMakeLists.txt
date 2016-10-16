cmake_minimum_required(VERSION 2.8)

project(SkySim)

set(CMAKE_CXX_FLAGS_RELEASE)
find_package(OpenCV REQUIRED)
add_executable(SkySim main.cpp)
target_link_libraries(SkySim ${OpenCV_LIBS})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pg")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -pg")
