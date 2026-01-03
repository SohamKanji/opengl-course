#pragma once

#include <GL/glew.h>
#include "stb_image.h"
#include <string>

class Texture
{

public:
    Texture();
    Texture(const std::string& file_location);

    ~Texture();

    bool loadTextureRGB();
    void loadTexture();
    void useTexture();
    void clearTexture();

private:

    GLuint m_texture_id;
    int m_width, m_height, m_bit_depth;
    std::string m_file_location;

};