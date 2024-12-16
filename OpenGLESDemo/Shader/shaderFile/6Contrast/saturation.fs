#version 300 es

precision mediump float;
out vec4 frag_colour;
in vec2 texCoord;
uniform sampler2D pic_texture;
uniform float slider_value;

// Values from "Graphics Shaders: Theory and Practice" by Bailey and Cunningham
const vec3 luminanceWeighting = vec3(0.2125, 0.7154, 0.0721);

void main() {
    vec4 textureColor = texture(pic_texture, texCoord);
    
    float luminance = dot(textureColor.rgb, luminanceWeighting);
    vec3 greyScaleColor = vec3(luminance);
    
    frag_colour = vec4(mix(greyScaleColor, textureColor.rgb, slider_value), textureColor.a);

}

