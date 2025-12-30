#include <iostream>
#include <GL/glew.h>
#include <string>
#include <vector>

class DirectionalLight;
class PointLight;
class SpotLight;

const static int MAX_POINT_LIGHT_COUNT = 3;
const static int MAX_SPOT_LIGHT_COUNT = 3;

class Shader {
    public:

    Shader();
    ~Shader();

    void createFromString(const std::string& vertex_code, const std::string& fragment_code);

    void createFromFiles(const std::string& vertex_location, const std::string& fragment_location);

    GLuint getUniformModel() const { return m_uniform_model; }

    GLuint getUniformProjection() const { return m_uniform_projection; }

    GLuint getUnifromView() const {return m_uniform_view;}

    GLuint getUniformSpecularIntensity() const {return m_uniform_specular_intensity;}

    GLuint getUniformShininess() const {return m_uniform_shininess;}

    GLuint getUniformEyePosition() const {return m_eye_position;}

    void clearShader();

    void useShader() const
    {
        glUseProgram(m_shader_id);
    }

    void useDirectionalLight(DirectionalLight* directional_light);

    void usePointLights(std::vector<PointLight*> point_lights);

    void useSpotLights(std::vector<SpotLight*> spot_lights);

    private:

    std::string readFile(const std::string& file_location);

    void addShader(GLuint the_program, const std::string& shader_code, GLenum shader_type);

    void compileShader(const std::string& vertex_code, const std::string& fragment_code);

    GLuint m_shader_id;
    GLuint m_uniform_model;
    GLuint m_uniform_projection;
    GLuint m_uniform_view;
    GLuint m_eye_position;
    GLuint m_uniform_shininess;
    GLuint m_uniform_specular_intensity;

    struct
    {
        GLuint diffuse_intensity;
        GLuint ambient_intensity;
        GLuint color;
        GLuint direction;
    } m_uniform_directional_light;

    struct 
    {
        GLuint diffuse_intensity;
        GLuint ambient_intensity;
        GLuint color;
        GLuint position;
        GLuint quadratic;
        GLuint linear;
        GLuint constant;
    } m_uniform_point_lights[MAX_POINT_LIGHT_COUNT];

    GLuint m_uniform_point_light_count;

    struct 
    {
        GLuint diffuse_intensity;
        GLuint ambient_intensity;
        GLuint color;
        GLuint position;
        GLuint quadratic;
        GLuint linear;
        GLuint constant;
        GLuint cutoff;
        GLuint direction;
    } m_uniform_spot_lights[MAX_SPOT_LIGHT_COUNT];

    GLuint m_uniform_spot_light_count;
};