cmake_minimum_required(VERSION 3.1.0)

project(IControlFussi)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 COMPONENTS Core Gui Widgets PrintSupport REQUIRED)

add_executable(IControlFussi
    src/main.cpp
    src/mainwindow.cpp
    src/mainwindow.h
    src/resources.qrc
)

target_link_libraries(IControlFussi PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::PrintSupport
)

