cmake_minimum_required(VERSION 3.17)
project(cluster_bots C)

set(CMAKE_C_STANDARD 11)


file(GLOB includes "../include/*.h")
file(GLOB bots "*.c")

add_executable(Cluster ${includes} ${bots})
include_directories(../include)
