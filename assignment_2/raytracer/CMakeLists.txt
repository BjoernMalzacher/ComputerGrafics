cmake_minimum_required (VERSION 3.9)
project (geometry)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_compile_options(-g -Wall -Wextra -Wpedantic -Wl,--stack,16777216)
add_executable(raytracer geometry.cc  math.cc raytracer.cc Raytracer_Renderer.cc )
target_link_libraries( raytracer SDL2)
add_compile_options(-fopenmp)

