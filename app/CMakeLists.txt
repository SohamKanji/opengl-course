add_executable(OpenGLProject main.cpp)

target_link_libraries(OpenGLProject glfw OpenGL::GL GLEW glm Mesh Shader GLWindow)