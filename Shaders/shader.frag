#version 330

in vec4 v_color;
in vec2 tex_coord;
in vec3 out_normal;

out vec4 color;

struct DirectionalLight
{
    vec3 color;
    float ambient_intensity;
    vec3 direction;
    float diffuse_intensity;
};

uniform sampler2D the_texture;
uniform DirectionalLight directional_light;

void main()
{   
    float diffuse_factor = max(dot(normalize(out_normal), normalize(directional_light.direction)), 0.0f); 
    vec4 diffuse_color = vec4(directional_light.color, 1.0f) * directional_light.diffuse_intensity * diffuse_factor;
    vec4 ambient_color = vec4(directional_light.color, 1.0f) * directional_light.ambient_intensity;

    color = texture(the_texture, tex_coord) * (ambient_color + diffuse_color);
}