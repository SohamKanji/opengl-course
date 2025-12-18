add_library(Material STATIC "material.cxx" "material.h")
target_include_directories(Camera PUBLIC  "./")
target_link_libraries(Camera GLEW)