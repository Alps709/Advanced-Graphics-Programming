#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 colour;

out VS_GS_VERTEX
{
	out vec4 position;
	out vec3 color;
	out mat4 mvp;
} vs_out;

uniform mat4 u_PVM;

void main(void)
{
	gl_Position = u_PVM * vec4(position, 1.0f);

	//Output to the geometry shader
	vs_out.color = color;
	vs_out.position = gl_Position;
	vs_out.mvp = mvp;
}