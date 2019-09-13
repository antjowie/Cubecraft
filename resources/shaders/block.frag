#version 450 core

in vec2 TexCoords;

out vec4 FragColor;

uniform sampler2D aTexture;

void main()
{
	FragColor = texture(aTexture,TexCoords);
}