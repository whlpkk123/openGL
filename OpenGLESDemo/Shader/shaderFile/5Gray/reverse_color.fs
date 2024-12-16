#version 300 es

precision mediump float;
out vec4 frag_colour;
in vec2 texCoord;
uniform sampler2D pic_texture;

void reverse_color(inout vec4 color){
    color.r = 1.0 - color.r;
    color.g = 1.0 - color.g;
    color.b = 1.0 - color.b;
}

void main() {
    vec4 textureColor = texture(pic_texture, texCoord);
    reverse_color(textureColor);
    frag_colour = textureColor;
}
