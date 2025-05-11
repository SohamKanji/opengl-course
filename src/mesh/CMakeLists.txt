add_library(Mesh STATIC "mesh.cxx" "mesh.h")
target_include_directories(Mesh PUBLIC  "./")
target_link_libraries(Mesh GLEW)