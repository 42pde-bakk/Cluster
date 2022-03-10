cmake_minimum_required(VERSION 3.17)
project(Cluster C)

set(CMAKE_C_STANDARD 11)


file(GLOB includes "include/*.h")
file(GLOB srcs "srcs/*.c")
file(GLOB srcs/output "srcs/output/*.c")
file(GLOB extra_srcs "srcs/**/*.c")
file(GLOB outside "*.c")

add_executable(Cluster ${includes} ${srcs} ${extra_srcs} ${output} ${outside})
include_directories(include)
include_directories(mlx/include)
