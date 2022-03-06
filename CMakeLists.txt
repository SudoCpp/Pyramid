cmake_minimum_required(VERSION 3.0.0)
project(Pyramid VERSION 1.0.0)

#Debian Packages required
# libsdl2-dev
# libsdl2-ttf-dev

set(Packages
    )

set(SubProjects
    simplextk
    simplexsdl
    ) 

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

        #Tabbed over values do not need to be edited
        if(NOT TARGET ${PROJECT_NAME})
add_library(${PROJECT_NAME} SHARED ${SourceFiles})
#target_link_libraries(${PROJECT_NAME} "-l_additional_libraries")
            # Unix systems required the dl library for dynamically loading libraries
            if (UNIX)
                target_link_libraries(${PROJECT_NAME} "-ldl")
            endif()

            # Include files for this project
            include_directories("include")

            # Go through all the packages that are required. Find them, and add support.
            foreach(Package IN LISTS Packages)
                find_package(${Package} REQUIRED)
                include_directories(${${Package}_INCLUDE_DIRS})
                target_link_libraries(${PROJECT_NAME} ${${Package}_LIBRARIES})
            endforeach()

            # Add all subprojects. 
            foreach(Project IN LISTS SubProjects)
                # This is like an include guard on a header file, they can only be added once
                if(NOT TARGET ${Project})
                    add_subdirectory("../${Project}")
                endif()
                include_directories("../${Project}")
                target_link_libraries(${PROJECT_NAME} ${Project})
            endforeach()

            if(EXISTS tests)
                include(CTest)
                enable_testing()
                #Add testing executables
                set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${FullOutputDir}/tests/${PROJECT_NAME}")
                add_subdirectory(tests)
                set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${FullOutputDir})
            endif()
        endif()

        #set(CPACK_PROJECT_NAME ${PROJECT_NAME})
        #set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
        #include(CPack)