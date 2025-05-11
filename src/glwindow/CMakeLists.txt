add_library(GLWindow STATIC "glwindow.cxx" "glwindow.h")
target_include_directories(GLWindow PUBLIC  "./")
target_link_libraries(GLWindow GLEW glfw)