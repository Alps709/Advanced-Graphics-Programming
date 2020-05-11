#version 450 core

uniform vec4 u_colour;

out vec4 colour;

void main()
{
	colour = u_colour;
}