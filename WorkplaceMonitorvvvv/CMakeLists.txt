cmake_minimum_required(VERSION 3.16)

project(WorkplaceMonitor LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")


find_package(Qt6 REQUIRED COMPONENTS Widgets Multimedia)

qt_standard_project_setup()

qt_add_executable(WorkplaceMonitor
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    camera_thread.h
    camera_thread.cpp
    mediapipe_pose.h
    mediapipe_pose.cpp
)

target_link_libraries(WorkplaceMonitor
    PRIVATE Qt6::Widgets
    PRIVATE Qt6::Multimedia
)
