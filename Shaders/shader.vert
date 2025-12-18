#version 330

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 tex;
layout(location = 2) in vec3 normal;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

out vec4 v_color;
out vec2 tex_coord;
out vec3 out_normal;
out vec3 frag_pos;

void main()
{
    gl_Position = projection * view * model * vec4(pos, 1.0);
    v_color = vec4(clamp(pos, 0.0, 1.0), 1.0);
    tex_coord = tex;
    out_normal = mat3(transpose(inverse(model))) * normal;
    frag_pos = (model * vec4(pos, 1.0)).xyz;
}