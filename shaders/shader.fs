#version 330 core
in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D image;
uniform sampler2D breakTexture;
uniform vec3 spriteColor;
uniform float breakAmount;

void main()
{
    vec4 texColor = texture(image, TexCoords);
    vec4 breakColor = texture(breakTexture, TexCoords);
    vec4 blended = mix(texColor, breakColor, breakAmount);
    FragColor = vec4(spriteColor, 1.0) * blended;
}