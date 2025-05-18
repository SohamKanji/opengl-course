#include "shader.h"
#include <fstream>

Shader::Shader() {
    m_shader_id = 0;
    m_uniform_model = 0;
    m_uniform_projection = 0;
    m_uniform_view = 0;
}

void Shader::clearShader()
{
    if(m_shader_id != 0) {
        glDeleteProgram(m_shader_id);
        m_shader_id = 0;
    }
    m_uniform_model = 0;
    m_uniform_projection = 0;
    m_uniform_view = 0;
}

void Shader::addShader(GLuint shader_program, const std::string& shader_code, GLenum shader_type)
{
    auto the_shader = glCreateShader(shader_type);

    const GLchar* the_code[1];
    the_code[0] = shader_code.c_str();

    GLint code_length[1];
    code_length[0] = shader_code.size();

    glShaderSource(the_shader, 1, the_code, code_length);
    glCompileShader(the_shader);

    GLint result = 0;
    GLchar eLog[1024] = {0};
    glGetShaderiv(the_shader, GL_COMPILE_STATUS, &result);
    if(!result) {
        glGetShaderInfoLog(the_shader, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error compiling the " << shader_type << " shader: " << eLog << std::endl;
        return;
    }

    glAttachShader(shader_program, the_shader);
}

void Shader::compileShader(const std::string& vertex_code, const std::string& fragment_code)
{
    m_shader_id = glCreateProgram();

    if(!m_shader_id) {
        std::cerr << "Error creating shader program" << std::endl;
        return;
    }

    addShader(m_shader_id, vertex_code, GL_VERTEX_SHADER);
    addShader(m_shader_id, fragment_code, GL_FRAGMENT_SHADER);

    GLint result = 0;
    GLchar eLog[1024] = {0};

    glLinkProgram(m_shader_id);
    glGetProgramiv(m_shader_id, GL_LINK_STATUS, &result);

    if(!result) {
        glGetProgramInfoLog(m_shader_id, sizeof(eLog), nullptr, eLog);
        std::cerr << "Error linking program: " << eLog << std::endl;
        return;
    }
    
    m_uniform_model = glGetUniformLocation(m_shader_id, "model");
    m_uniform_projection = glGetUniformLocation(m_shader_id, "projection");
    m_uniform_view = glGetUniformLocation(m_shader_id, "view");
}

Shader::~Shader()
{
    clearShader();
}

void Shader::createFromString(const std::string& vertex_code, const std::string& fragment_code)
{
    compileShader(vertex_code, fragment_code);
}

void Shader::createFromFiles(const std::string& vertex_location, const std::string& fragment_location)
{
    auto vertex_code = readFile(vertex_location);
    auto fragment_code = readFile(fragment_location);

    createFromString(vertex_code, fragment_code);
}

std::string Shader::readFile(const std::string& file_location)
{
    std::fstream file_stream(file_location.c_str(), std::ios::in);

    if(!file_stream) {
        std::cerr << "Failed to read file: " << file_location << std::endl;
        return "";
    }

    std::string result;

    std::string line = "";
    while(!file_stream.eof()) {
        std::getline(file_stream, line);
        result.append(line + "\n");
    }

    return result;
}