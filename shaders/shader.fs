#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform sampler2D breakTexture;
uniform vec3 spriteColor;
uniform float breakAmount;
uniform float frame;
uniform float framesPerRow;
uniform float frameSize;
uniform float frameRows;

void main()
{
    // animation
    float row = floor(frame / framesPerRow);
    float col = mod(frame, framesPerRow);

    vec2 animTexCoords;
    animTexCoords.x = (col + TexCoords.x) * frameSize;
    animTexCoords.y = (row + TexCoords.y) * frameSize;
    // simple sprites
    vec4 texColor = texture(image, TexCoords);
    vec4 breakColor = texture(breakTexture, TexCoords);
    vec4 blended = mix(texColor, breakColor, breakAmount);
    FragColor = vec4(spriteColor, 1.0) * blended;
}