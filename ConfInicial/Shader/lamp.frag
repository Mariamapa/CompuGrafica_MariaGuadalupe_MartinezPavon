#version 330 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D lampTexture;

void main()
{
    vec4 texColor = texture(lampTexture, TexCoords);

    if (texColor.a < 0.1)
        discard;

    FragColor = texColor;
}
