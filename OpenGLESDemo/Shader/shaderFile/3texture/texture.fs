#version 300 es

precision mediump float;
out vec4 frag_colour;

in vec3 colour;
in vec2 texCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform float alpha;

void main() {
    vec4 color1 = texture(texture1, texCoord);
    vec4 color2 = texture(texture2, texCoord);
    
    if (color2.a <= 0.0) {
        frag_colour = color1;
    }else {
        frag_colour = mix(color1 ,color2, alpha);
    }
}
