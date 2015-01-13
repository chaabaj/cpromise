cmake_minimum_required(VERSION 2.8.4)
project(CPromise)


file(GLOB_RECURSE SRCS "src/*.c")
file(GLOB_RECURSE HEADERS "include/*.h")

include_directories(include ../core/include)

add_executable(CPromise ${SRCS})