#version 300 es
layout (location = 0) in vec3 vertexPosition;
layout (location = 1) in vec2 aTexCoord;

out vec2 textureCoordinate;
out vec2 leftTextureCoordinate;
out vec2 rightTextureCoordinate;
out vec2 topTextureCoordinate;
out vec2 bottomTextureCoordinate;
out float centerMultiplier;
out float edgeMultiplier;

uniform vec2 imageFactor;
uniform float sharpness;


void main(void) {
    gl_Position = vec4(vertexPosition.xyz, 1.0);

    textureCoordinate = aTexCoord.xy;
    leftTextureCoordinate = aTexCoord.xy - vec2(imageFactor.x, 0);
    rightTextureCoordinate = aTexCoord.xy + vec2(imageFactor.x, 0);
    topTextureCoordinate = aTexCoord.xy + vec2(0, imageFactor.y);
    bottomTextureCoordinate = aTexCoord.xy - vec2(0, imageFactor.y);

    centerMultiplier = 1.0 + 4.0 * sharpness;
    edgeMultiplier = sharpness;
}
