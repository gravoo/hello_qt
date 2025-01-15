cmake_minimum_required(VERSION 3.19)
project(hello_qt)
find_package(Boost REQUIRED)

add_subdirectory(client)
add_subdirectory(server)

