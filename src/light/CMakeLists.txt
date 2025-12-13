add_library(Light STATIC "light.cxx" "light.h")
target_include_directories(Light PUBLIC  "./")
target_link_libraries(Light GLEW glm)