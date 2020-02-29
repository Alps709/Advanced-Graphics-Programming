#version 450 core

in vec3 fragmentTextureCoord;

out vec4 colour;

uniform samplerCube u_cubeSampler;

void main()
{
	colour = texture(u_cubeSampler, fragmentTextureCoord);
}