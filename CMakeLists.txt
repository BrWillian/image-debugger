cmake_minimum_required(VERSION 3.5)

project(image_debug LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

find_package(Qt5 COMPONENTS Widgets REQUIRED)

add_executable(image_debug
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    file_utils.cpp
    file_utils.h
    image_utils.h
    image_utils.cpp
)

target_link_libraries(image_debug PRIVATE Qt5::Widgets)
