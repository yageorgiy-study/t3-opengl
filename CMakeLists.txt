cmake_minimum_required(VERSION 3.16)
project(app VERSION 0.1.0 DESCRIPTION "OpenGL application")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

set(FILES
    include/tiny_obj_loader.h
    src/main.cpp

    src/window.h
    src/window.cpp
    src/scene.h
    src/scene.cpp
    src/logger.h
    src/logger.cpp

    src/sceneobjects/sceneobject.h
    src/sceneobjects/sceneobject.cpp



    src/light/dirlight.cpp
    src/light/dirlight.h
    src/light/lightsinfo.cpp
    src/light/lightsinfo.h
    src/light/pointlight.cpp
    src/light/pointlight.h
    src/light/spotlight.cpp
    src/light/spotlight.h

    src/shaders/program.h
    src/shaders/program.cpp
    src/shaders/shader.h
    src/shaders/shader.cpp
    src/shaders/compilestatus.h
    src/shaders/argumenttype.h
    src/shaders/drawmethod.h
    src/shaders/data.h
    src/shaders/data.cpp

    src/assets/texture.h
    src/assets/texture.cpp
    src/assets/cubemap.h
    src/assets/cubemap.cpp
    src/assets/texturestatus.h
    src/assets/material.cpp
    src/assets/material.h
    src/assets/assetmanager.cpp
    src/assets/assetmanager.h
    src/assets/model.cpp
    src/assets/model.h
)

# configure_file("resources/shaders/" "${CMAKE_BINARY_DIR}/resources/shaders/" COPYONLY)
# configure_file("resources/models/" "${CMAKE_BINARY_DIR}/resources/models/" COPYONLY)

file(COPY "resources/shaders/" DESTINATION "${CMAKE_BINARY_DIR}/resources/shaders/")
file(COPY "resources/models/" DESTINATION "${CMAKE_BINARY_DIR}/resources/models/")
file(COPY "resources/textures/" DESTINATION "${CMAKE_BINARY_DIR}/resources/textures/")

add_executable(app ${FILES})
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)
include_directories(${GLEW_INCLUDE_DIRS})
link_libraries(${GLEW_LIBRARIES})

set(GL_LIBRARY GL GLU X11)
target_link_libraries(app SOIL glfw GL X11 pthread Xrandr Xi dl GLEW GLU glm)
