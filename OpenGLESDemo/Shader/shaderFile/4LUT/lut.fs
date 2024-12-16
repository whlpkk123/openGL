#version 300 es

precision mediump float;
out vec4 frag_colour;

in vec2 texCoord;

uniform sampler2D pic_texture;
uniform sampler2D lut_texture;

void main() {
    vec4 textureColor = texture(pic_texture, texCoord);
    
    vec3 rgbColor = textureColor.rgb * 63.0;

    vec2 quad;
    quad.y = floor(floor(rgbColor.b) / 8.0);
    quad.x = floor(rgbColor.b) - (quad.y * 8.0);

    vec2 texPos;
    texPos.x = (quad.x * 64.0 + rgbColor.r + 0.5)/512.0;
    texPos.y = (quad.y * 64.0 + rgbColor.g + 0.5)/512.0;

    vec4 newColor1 = texture(lut_texture, texPos);
    frag_colour = newColor1;
}
