#version 450 core

layout (points) in;
layout (triangle_strip, max_vertices = 12) out;

in VS_GS_VERTEX
{
	in vec4 position;
	in mat4 pvm;
}gs_in[];

void main() 
{
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.0f, -0.25f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.0f,  0.25f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.5f,  0.0f,  0.0f); EmitVertex();
	EndPrimitive();

	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.0f, -0.25f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.0f,  0.25f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f, -0.5f,  0.0f,  0.0f); EmitVertex();
	EndPrimitive();

	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.25f, 0.0f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.0f, -0.5f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f, -0.25f, 0.0f, 0.0f); EmitVertex();
	EndPrimitive();

	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f, -0.25f, 0.0f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.0f,  0.5f, 0.0f); EmitVertex();
	gl_Position = gs_in[0].position + gs_in[0].pvm * vec4(0.0f,  0.25f, 0.0f, 0.0f); EmitVertex();
	EndPrimitive();
}