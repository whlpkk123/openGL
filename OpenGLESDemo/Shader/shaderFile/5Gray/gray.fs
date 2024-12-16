#version 300 es

precision mediump float;
out vec4 frag_colour;
in vec2 texCoord;
uniform sampler2D pic_texture;

void grey(inout vec4 color){
    float weightMean = color.r * 0.3 + color.g * 0.59 + color.b * 0.11;
    color.r = color.g = color.b = weightMean;
}

void main() {
    vec4 textureColor = texture(pic_texture, texCoord);
    grey(textureColor);
    frag_colour = textureColor;
}
