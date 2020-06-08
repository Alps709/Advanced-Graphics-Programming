#version 450 core

uniform vec4 u_colour = vec4(0.2f, 0.5f, 1.0f, 1.0f);

out vec4 colour;

void main()
{
	colour = u_colour;
}