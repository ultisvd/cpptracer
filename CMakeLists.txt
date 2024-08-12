cmake_minimum_required(VERSION 3.22)

project(
  Cpptracer
  VERSION 1.0
  DESCRIPTION "Raytracer in C++"
  LANGUAGES CXX)

add_executable(tracer main.cpp src/vec3.cpp src/color.cpp src/ray.cpp)

set(CMAKE_CXX_FLAGS
    "-std=c++20 -Wall -Wextra -Wpedantic -Wconversion -fno-exceptions -O3")

target_include_directories(tracer PUBLIC include)

set_target_properties(tracer PROPERTIES CXX_STANDARD 23)
