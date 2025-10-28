cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)

set(CMAKE_AUTOMOC ON)

add_library(Common STATIC
    BaseWindow.cpp
    BaseWindow.h
)
target_include_directories(Common PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

target_link_libraries(Common PUBLIC Qt5::Core Qt5::Widgets)

