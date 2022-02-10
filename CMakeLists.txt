cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)

#create Project
project(learnOpenGL)

#add custom target for copying resource files to binary folder
add_custom_target(
        copy-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/res
        )

add_dependencies(${PROJECT_NAME} copy-files)

#add source files
add_executable(learnOpenGL main.cpp)

#add c++ macro definitions
add_definitions()


#find and link libraries to executable
#for windows
if(WIN32)
    
    #find lib
    find_package(OpenGL REQUIRED)
    
    #includes
    include_directories(
            "${CMAKE_SOURCE_DIR}\\Dependencies\\GLFW\\include"
            "${CMAKE_SOURCE_DIR}\\Dependencies\\glew-2.1.0\\include"
            ${OPENGL_INCLUDE_DIRS}
    )

    #libs
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}
            "${CMAKE_SOURCE_DIR}\\Dependencies\\GLFW\\lib-mingw-w64\\libglfw3.a"
            "${CMAKE_SOURCE_DIR}\\Dependencies\\glew-2.1.0\\lib\\Release\\x64\\glew32s.lib"
            ${OPENGL_LIBRARIES}
    )
endif()

#for mac
if(APPLE)

    #find lib
    find_package(OpenGL REQUIRED)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)

    #includes
    include_directories(
            "${CMAKE_SOURCE_DIR}/Dependencies/GLFW-Mac/include"
            "${CMAKE_SOURCE_DIR}/Dependencies/glew-2.1.0-Mac/include"
            ${OPENGL_INCLUDE_DIRS}

    )

    #libs
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}
            "${CMAKE_SOURCE_DIR}/Dependencies/GLFW-Mac/lib-arm64/libglfw3.a"
            "${CMAKE_SOURCE_DIR}/Dependencies/glew-2.1.0-Mac/lib/libGLEW.a"
            ${COCOA_LIBRARY}
            ${OPENGL_LIBRARIES}
            ${IOKIT_LIBRARY}
    )
endif()