#version 300 es

precision mediump float;
out vec4 frag_colour;

in vec2 textureCoordinate;
in vec2 leftTextureCoordinate;
in vec2 rightTextureCoordinate;
in vec2 topTextureCoordinate;
in vec2 bottomTextureCoordinate;
in float centerMultiplier;
in float edgeMultiplier;

uniform sampler2D pic_texture;

void main() {
    vec4 textureColor = texture(pic_texture, textureCoordinate);
    vec4 leftTextureColor = texture(pic_texture, leftTextureCoordinate);
    vec4 rightTextureColor = texture(pic_texture, rightTextureCoordinate);
    vec4 topTextureColor = texture(pic_texture, topTextureCoordinate);
    vec4 bottomTextureColor = texture(pic_texture, bottomTextureCoordinate);

    frag_colour = vec4((textureColor * centerMultiplier- (leftTextureColor + rightTextureColor + topTextureColor + bottomTextureColor) * edgeMultiplier).rgb, textureColor.a);
}
