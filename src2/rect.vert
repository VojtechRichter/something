#version 300 es

precision mediump float;

layout(location = 1) in vec2 vertex_position;
layout(location = 2) in vec4 vertex_color;

// TODO: ratio is hardcoded in rect.vert shader
#define RATIO (600.0 / 800.0)

out vec4 color;

void main() {
    gl_Position = vec4(vertex_position * vec2(RATIO, 1.0), 0.0, 1.0);
    color = vertex_color;
}
