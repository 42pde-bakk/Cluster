cmake_minimum_required(VERSION 3.17)
project(Cluster C)

set(CMAKE_C_STANDARD 99)

file(GLOB includes "include/*.h")
file(GLOB srcs "srcs/*.c")
file(GLOB extra_srcs "srcs/**/*.c")

add_executable(Cluster ${includes} ${srcs} ${extra_srcs})
include_directories(include)
