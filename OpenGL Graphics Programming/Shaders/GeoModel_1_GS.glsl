#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 3) out;

in VS_GS_VERTEX
{
	in vec4 position;
	in vec3 color;
	in mat4 mvp;
}gs_in[];

out vec3 outColor;

void main() 
{
	outColor = gs_in[0].color;

	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(-2.0f, 0.0f, 0.0f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(2.0f, 0.0f, 0.0f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].mvp * vec4(0.0f, 2.0f, 0.0f, 0.0f); EmitVertex();
	EndPrimitive();
}