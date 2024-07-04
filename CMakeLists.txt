cmake_minimum_required(VERSION 3.10)
project(Aether)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.cpp")
include_directories(SYSTEM "src/include")

add_executable(aether ${SOURCES})
