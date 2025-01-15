cmake_minimum_required(VERSION 3.19)
project(hello_qt)

find_package(Boost REQUIRED)
find_package(Qt6 COMPONENTS Widgets REQUIRED)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

add_subdirectory(client)
add_subdirectory(server)

