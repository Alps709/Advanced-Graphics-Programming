#version 450 core

in vec2 fragmentTextureCoord;

out vec4 colour;

uniform sampler2D u_renderTex;

void main(void)
{
	colour = texture(u_renderTex, fragmentTextureCoord);
}