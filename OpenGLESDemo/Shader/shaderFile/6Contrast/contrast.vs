#version 300 es
layout(location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 texCoord;

void main(void) {
    texCoord = aTexCoord;
    gl_Position = vec4(vertexPosition.xyz, 1.0);
}

