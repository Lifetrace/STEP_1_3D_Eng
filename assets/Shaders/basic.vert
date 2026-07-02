#version 460 core

in layout(location = 0) vec3 v_position;
in layout(location = 1) vec4 v_color;
in layout(location = 2) vec2 v_textCoord;

out vec4 out_color;
out vec2 a_textCoord;

void main() {
    gl_Position = vec4(v_position, 1.0);
    a_textCoord = v_textCoord;
    out_color = v_color;
}
