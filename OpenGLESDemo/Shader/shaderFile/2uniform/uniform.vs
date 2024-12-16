#version 300 es
layout(location = 0) in vec4 vertexPosition;
uniform vec2 ourOffset;

void main(void) {
    gl_Position = vec4(vertexPosition.x + ourOffset.x, vertexPosition.y + ourOffset.y, vertexPosition.z, 1.0);
;
}

