add_library(Camera STATIC "camera.cxx" "camera.h")
target_include_directories(Camera PUBLIC  "./")
target_link_libraries(Camera GLEW glfw glm)