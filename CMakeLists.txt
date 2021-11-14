cmake_minimum_required(VERSION 3.20)
project(RTSkippy)

set(CMAKE_CXX_STANDARD 23)

# Add useful packages
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)


# Include Directories
include_directories(include ressources ${OPENGL_INCLUDE_DIRS}  ${GLEW_LIBRARY})
set(SOURCES src/main.cpp src/Shader.cpp src/EBO.cpp src/VBO.cpp src/VAO.cpp)

add_executable(RTSkippy ${SOURCES})
target_link_libraries(${PROJECT_NAME} -lGL -lGLU -lGLEW -lglfw -lpthread)
