#version 450 core

layout (location = 0) in vec3 position;

out VS_GS_VERTEX
{
	out vec4 position;
	out mat4 pvm;
} vs_out;

uniform mat4 u_PVM;

void main(void)
{
	gl_Position = u_PVM * vec4(position, 1.0f);

	//Output to the geometry shader
	vs_out.position = gl_Position;
	vs_out.pvm = u_PVM;
}