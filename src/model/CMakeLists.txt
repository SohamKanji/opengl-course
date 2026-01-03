add_library(Model STATIC "model.cxx" "model.h") 
target_include_directories(Model PUBLIC  "./")
target_link_libraries(Model Texture Mesh assimp::assimp GLEW) 