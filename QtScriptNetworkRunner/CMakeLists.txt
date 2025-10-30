cmake_minimum_required(VERSION 3.16)

project(QtScriptNetworkRunner VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Core Widgets Network REQUIRED)

set(SOURCES
    main.cpp
    QtScriptNetworkRunner.cpp
    QtScriptNetworkRunner.ui
)

set(HEADERS
    QtScriptNetworkRunner.h
)

set(FORMS
    QtScriptNetworkRunner.ui
    )

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

add_executable(${PROJECT_NAME} WIN32 ${SOURCES} ${HEADERS} ${UI_HEADERS})

target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core Qt5::Widgets Qt5::Network Common)

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/../Common
    )
