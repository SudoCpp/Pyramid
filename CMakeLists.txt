cmake_minimum_required(VERSION 3.0.0)
project(Pyramid VERSION 1.0.0)

include_directories("include")
include_directories("..")

set(LinkedLibraryNames
    simplextk
    simplexsdl)

set(SourceFiles
    src/Button.cpp
    src/Canvas.cpp
    src/CMYColor.cpp
    src/Defaults.cpp
    src/Label.cpp
    src/Menu.cpp
    src/MenuBar.cpp
    src/MessageBox.cpp
    src/Pyramid.cpp
    src/RGBColor.cpp
    src/StatusBar.cpp
    src/TableContainer.cpp
    src/Widget.cpp
    src/WidgetContainer.cpp
    src/Window.cpp
    )

if(NOT TARGET ${PROJECT_NAME})
    add_library(${PROJECT_NAME} SHARED ${SourceFiles})
    target_link_libraries(${PROJECT_NAME} ${LinkedLibraryNames})
endif()