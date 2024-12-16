#version 300 es

precision mediump float;
out vec4 frag_colour;
in vec2 texCoord;
uniform sampler2D pic_texture;
uniform float slider_value;

void main() {
    vec4 textureColor = texture(pic_texture, texCoord);
    frag_colour = vec4(((textureColor.rgb - vec3(0.5)) * slider_value + vec3(0.5)), textureColor.a);
}

