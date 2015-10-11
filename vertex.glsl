#version 420 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec2 tex_coords;

out vec2 v_tex_coords;

uniform mat4 proj;

void main() {
    gl_Position = proj * vec4(position, 1.0);
    v_tex_coords = tex_coords;
};

