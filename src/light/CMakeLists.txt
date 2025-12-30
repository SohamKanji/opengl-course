add_library(Light STATIC "light.cxx" "light.h" "directional_light.h" "directional_light.cxx" "point_light.h" "point_light.cxx" "spot_light.h" "spot_light.cxx") 
target_include_directories(Light PUBLIC  "./")
target_link_libraries(Light GLEW glm)