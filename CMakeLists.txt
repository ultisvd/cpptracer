cmake_minimum_required(VERSION 3.22)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(
  Cpptracer
  VERSION 1.0
  DESCRIPTION "Raytracer in C++"
  )

include(FetchContent)

FetchContent_Declare(
  glm
  GIT_REPOSITORY https://github.com/g-truc/glm.git
  GIT_TAG master
  GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(glm)

add_subdirectory(lib/SDL EXCLUDE_FROM_ALL)

add_executable(tracer main.cpp src/camera.cpp src/ray.cpp src/glad.c)

find_package(TBB REQUIRED COMPONENTS tbb)

set(CMAKE_CXX_FLAGS
    "-std=c++20 -Wall -Wextra -Wpedantic -Wconversion -flto \
    -Ofast -Wconversion -Wimplicit-fallthrough -Wno-uninitialized \
    -Werror=format-security -U_FORTIFY_SOURCE -D_FORTIFY_SOURCE=3 -Wformat \
    -Wformat=2 -D_GLIBCXX_ASSERTIONS \
    -fstack-protector-strong -Wl,-z,nodlopen -Wl,-z,noexecstack \
    -Wl,-z,relro -Wl,-z,now -ggdb")
set(CMAKE_EXE_LINKER_FLAGS "-Ofast -flto")

target_include_directories(tracer PUBLIC include)
target_include_directories(tracer PUBLIC include/glad)
target_include_directories(tracer PUBLIC include/KHR)

set_target_properties(tracer PROPERTIES CXX_STANDARD 23)

target_link_libraries(tracer glm::glm -flto)
target_link_libraries(tracer tbb -flto)
target_link_libraries(tracer SDL3::SDL3 -flto)

