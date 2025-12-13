add_library(Texture STATIC "texture.cxx" "texture.h")
target_include_directories(Texture PUBLIC  "./")
target_link_libraries(Texture GLEW STBImage) 