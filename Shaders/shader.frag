#version 330

in vec4 v_color;
in vec2 tex_coord;
in vec3 out_normal;
in vec3 frag_pos;

out vec4 color;

const int MAX_POINT_LIGHT_COUNT = 3;
const int MAX_SPOT_LIGHT_COUNT = 3;

struct Light 
{
    vec3 color;
    float ambient_intensity;
    float diffuse_intensity;
};

struct DirectionalLight
{
    Light base;
    vec3 direction;
};

struct PointLight
{  
    Light base;
    vec3 position;
    float quadratic;
    float linear;
    float constant;
};

struct SpotLight 
{
    PointLight base;
    vec3 direction;
    float cutoff;
};

struct Material
{
    float shininess;
    float specular_intensity;
};

uniform sampler2D the_texture;
uniform DirectionalLight directional_light;
uniform PointLight point_lights[MAX_POINT_LIGHT_COUNT];
uniform int point_light_count;
uniform SpotLight spot_lights[MAX_SPOT_LIGHT_COUNT];
uniform int spot_light_count;
uniform Material material;
uniform vec3 eye_position;

vec4 calcColorByDirection(Light light, vec3 direction)
{
   float diffuse_factor = max(dot(normalize(out_normal), normalize(direction)), 0.0f); 
   vec4 diffuse_color = vec4(light.color, 1.0f) * light.diffuse_intensity * diffuse_factor;
   vec4 ambient_color = vec4(light.color, 1.0f) * light.ambient_intensity;
   vec4 specular_color = vec4(0.0f, 0.0f, 0.0f, 0.0f);

   if(diffuse_factor > 0.0f) {
       vec3 frag_to_eye = normalize(eye_position - frag_pos);
       vec3 reflected_vertex = normalize(reflect(direction, normalize(out_normal)));
       float specular_factor = dot(frag_to_eye, reflected_vertex);
       if (specular_factor > 0.0f) {
           specular_factor = pow(specular_factor, material.shininess);
           specular_color = vec4(light.color * material.specular_intensity * specular_factor, 1.0f);
       }
   } 
   return (ambient_color + diffuse_color + specular_color);
}

vec4 calcDirectionalLight()
{
    return calcColorByDirection(directional_light.base, directional_light.direction);
}

vec4 calcPointLightColor(PointLight point_light)
{
    vec3 direction = frag_pos - point_light.position;
    float distance = length(direction);
    direction = normalize(direction);
    vec4 color = calcColorByDirection(point_light.base, direction);
    float attenuation = point_light.quadratic*distance*distance + point_light.linear*distance + point_light.constant;
    return (color/attenuation);
}

vec4 calcPointLights()
{
    vec4 result = vec4(0,0,0,0);
    for(int i=0; i<point_light_count; i++) {
        result += calcPointLightColor(point_lights[i]);
    }
    return result;
}

vec4 calcSpotLights()
{
    vec4 result = vec4(0,0,0,0);
    for(int i=0; i<spot_light_count; i++) {
        vec3 light_to_fragment = frag_pos - spot_lights[i].base.position;
        float angle_to_fragment = dot(light_to_fragment, spot_lights[i].direction);
        if (angle_to_fragment > spot_lights[i].cutoff) {
            float spot_light_fade = 1.0f - ((1.0f - angle_to_fragment)/(1.0f - spot_lights[i].cutoff));
            result += calcPointLightColor(spot_lights[i].base)*spot_light_fade;
        }
    }
    return result;
}

void main()
{   
    vec4 final_color = calcDirectionalLight();
    final_color += calcPointLights();
    final_color += calcSpotLights();

    color = texture(the_texture, tex_coord) * final_color;
}