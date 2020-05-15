#version 450 core

layout (location = 0) in vec3 position;

uniform mat4 u_PVM;

void main(void)
{
	gl_Position = u_PVM * vec4(position, 1.0f);
}