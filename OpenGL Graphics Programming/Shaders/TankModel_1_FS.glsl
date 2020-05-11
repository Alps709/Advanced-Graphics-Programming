#version 450 core

in vec2 fragmentTextureCoord;

out vec4 colour;

uniform sampler2D texture_diffuse1;

void main(void)
{
	colour = texture(texture_diffuse1, fragmentTextureCoord);
}