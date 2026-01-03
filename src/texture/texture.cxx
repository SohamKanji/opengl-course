#include "texture.h"
#include <iostream>

using namespace std;

Texture::Texture() : m_texture_id(0), m_width(0), m_height(0), m_bit_depth(0), m_file_location(std::string())
{
}

Texture::Texture(const std::string& file_location) : m_texture_id(0), m_width(0), m_height(0), m_bit_depth(0), m_file_location(file_location)
{
}

bool Texture::loadTextureRGB()
{
    auto tex_data = stbi_load(m_file_location.c_str(), &m_width, &m_height, &m_bit_depth, 0);
    if(tex_data == nullptr) {
        cout << "Failed to find " << m_file_location << endl;
        return false;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_width, m_height, 0, GL_RGB, GL_UNSIGNED_BYTE, tex_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(tex_data);
    return true;
}

void Texture::loadTexture()
{
    auto tex_data = stbi_load(m_file_location.c_str(), &m_width, &m_height, &m_bit_depth, 0);
    if(tex_data == nullptr) {
        cout << "Failed to find " << m_file_location << endl;
        return;
    }

    glGenTextures(1, &m_texture_id);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, tex_data);
    glGenerateMipmap(GL_TEXTURE_2D);

    glBindTexture(GL_TEXTURE_2D, 0);
    stbi_image_free(tex_data);
}

void Texture::clearTexture()
{
    glDeleteTextures(1, &m_texture_id);
    m_texture_id = 0;
    m_width = 0;
    m_height = 0;
    m_bit_depth = 0;
    m_file_location = string();
}

Texture::~Texture() 
{
    clearTexture();
}

void Texture::useTexture()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture_id);
}