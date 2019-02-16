#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

// texture sampler
uniform sampler2D Texture;
uniform vec4 ColorMask;

void main()
{
	FragColor = texture(Texture, TexCoord) * ColorMask;
}
