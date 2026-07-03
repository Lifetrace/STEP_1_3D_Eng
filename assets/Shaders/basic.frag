#version 460 core

in vec4 out_color;
in vec2 a_textCoord;
out vec4 f_color;

uniform sampler2D u_texture0;

void main() {
    //f_color = out_color * texture(u_texture0, a_textCoord);
    f_color = out_color;
}
