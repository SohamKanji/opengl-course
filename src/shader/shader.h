#include <iostream>
#include <GL/glew.h>
#include <string>

class Shader {
    public:

    Shader();
    ~Shader();

    void createFromString(const std::string& vertex_code, const std::string& fragment_code);

    void createFromFiles(const std::string& vertex_location, const std::string& fragment_location);

    GLuint getUniformModel() const { return m_uniform_model; }

    GLuint getUniformProjection() const { return m_uniform_projection; }

    GLuint getUnifromView() const {return m_uniform_view;}

    GLuint getUniformColor() const {return m_uniform_color;}

    GLuint getUniformAmbientIntensity() const {return m_ambient_intensity;}

    GLuint getUniformDirection() const {return m_direction;}

    GLuint getUniformDiffuseIntensity() const {return m_diffuse_intensity;}

    void clearShader();

    void useShader() const
    {
        glUseProgram(m_shader_id);
    }

    private:

    std::string readFile(const std::string& file_location);

    void addShader(GLuint the_program, const std::string& shader_code, GLenum shader_type);

    void compileShader(const std::string& vertex_code, const std::string& fragment_code);

    GLuint m_shader_id;
    GLuint m_uniform_model;
    GLuint m_uniform_projection;
    GLuint m_uniform_view;
    GLuint m_uniform_color;
    GLuint m_ambient_intensity;
    GLuint m_direction;
    GLuint m_diffuse_intensity;
};