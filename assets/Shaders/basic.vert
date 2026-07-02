#version 460 core

in layout(location = 0) vec3 v_position;
in layout(location = 1) vec4 v_color;

out vec4 out_color;

void main() {
    gl_Position = vec4(v_position, 1.0);
    out_color = v_color;
}
