cmake_minimum_required(VERSION 3.22)

project(
  Cpptracer
  VERSION 1.0
  DESCRIPTION "Raytracer in C++"
  LANGUAGES CXX)

add_executable(tracer main.cpp src/camera.cpp src/ray.cpp)

find_package(raylib REQUIRED)
find_package(glm REQUIRED)
find_package(TBB REQUIRED COMPONENTS tbb)

set(CMAKE_CXX_FLAGS
    "-std=c++20 -Wall -Wextra -Wpedantic -Wconversion -fopenmp \
    -Ofast -Wconversion -Wimplicit-fallthrough -Wno-uninitialized \
    -Werror=format-security -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 -Wformat -Wformat=2 \
    -D_GLIBCXX_ASSERTIONS  -fstack-clash-protection -fstack-protector-strong \
    -Wl,-z,nodlopen -Wl,-z,noexecstack \
    -Wl,-z,relro -Wl,-z,now -ggdb")

target_include_directories(tracer PUBLIC include)

set_target_properties(tracer PROPERTIES CXX_STANDARD 23)

target_link_libraries(tracer raylib)
target_link_libraries(tracer glm::glm)
target_link_libraries(tracer tbb)
