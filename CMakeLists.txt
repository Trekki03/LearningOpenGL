cmake_minimum_required(VERSION 3.21)
set(CMAKE_CXX_STANDARD 23)
#create Project
project(learnOpenGL)

#add source files
add_executable(
        learnOpenGL
        src/main.cpp
        dependencies/glad/src/glad.c # --> Glad-lib src file
        src/VertexBuffer.cpp
        src/VertexBuffer.h
        src/IndexBuffer.cpp
        src/IndexBuffer.h src/VertexArrayObject.cpp src/VertexArrayObject.h src/window_processing.cpp src/window_processing.h src/ShaderProgram.cpp src/ShaderProgram.h src/Texture2D.cpp src/Texture2D.h)


#add custom target for copying resource files to binary folder
add_custom_target(
        copy-files ALL
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/res
        ${CMAKE_BINARY_DIR}/res
)
add_dependencies(${PROJECT_NAME} copy-files)

#find and add libraries
find_package(OpenGL REQUIRED)
include_directories(
        ${OPENGL_INCLUDE_DIRS}
        "${CMAKE_SOURCE_DIR}/dependencies/glfw/include"
        "${CMAKE_SOURCE_DIR}/dependencies/glad/include"
        "${CMAKE_SOURCE_DIR}/dependencies/stb/include"
)
target_link_libraries(
        ${CMAKE_PROJECT_NAME}
        ${OPENGL_LIBRARIES}

        "${CMAKE_SOURCE_DIR}/dependencies/glfw/lib/libglfw3.a"
)

#add mac specific libraries
if(APPLE)
    find_library(COCOA_LIBRARY Cocoa)
    find_library(IOKIT_LIBRARY IOKit)
    target_link_libraries(
            ${CMAKE_PROJECT_NAME}
            ${COCOA_LIBRARY}
            ${IOKIT_LIBRARY}
    )
endif()
