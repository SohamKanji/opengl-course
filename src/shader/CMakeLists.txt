add_library(Shader STATIC "shader.cxx" "shader.h")
target_include_directories(Shader PUBLIC  "./")
target_link_libraries(Shader GLEW)