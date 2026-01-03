cmake_minimum_required(VERSION 3.16)
project(OpenGLProject)

set(CMAKE_CXX_STANDARD 20)

# Find GLFW and GLEW
find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glm REQUIRED)

# Include directories
include_directories(/opt/homebrew/include)

# Link directories
link_directories(/opt/homebrew/lib)

include(FetchContent)

FetchContent_Declare(
    assimp
    GIT_REPOSITORY https://github.com/assimp/assimp.git
    GIT_TAG v6.0.2
    GIT_SHALLOW TRUE
)
FetchContent_MakeAvailable(assimp)

add_subdirectory(app)
add_subdirectory(src)

