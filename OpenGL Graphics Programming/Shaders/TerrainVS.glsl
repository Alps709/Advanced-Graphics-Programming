#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;

uniform int u_time;
uniform mat4 u_PVM;

out vec3 fragmentColour;

vec3 colour = vec3(0.0f, 1.0f, 0.0f);

void main(void)
{
	gl_Position = u_PVM * vec4(position, 1.0f);
	fragmentColour = colour;
}