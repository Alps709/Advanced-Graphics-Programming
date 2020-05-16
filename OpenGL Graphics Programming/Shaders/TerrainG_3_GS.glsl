#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 12) out;

in VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_GS_in[];

out VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_FS_in;

uniform mat4 u_PVM;
uniform mat4 u_PV;

void main() 
{
	gl_Position = u_PV * vertex_info_GS_in[0].WorldPos; 
	vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
	vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
	vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
	vertex_info_FS_in.TexCoord = vertex_info_GS_in[0].TexCoord;
	EmitVertex();

	gl_Position = u_PV * vertex_info_GS_in[1].WorldPos; 
	vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[1].WorldPos;
	vertex_info_FS_in.FragPos = vertex_info_GS_in[1].FragPos;
	vertex_info_FS_in.Normal   = vertex_info_GS_in[1].Normal;
	vertex_info_FS_in.TexCoord = vertex_info_GS_in[1].TexCoord;
	EmitVertex();

	gl_Position = u_PV * vertex_info_GS_in[2].WorldPos; 
	vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[2].WorldPos;
	vertex_info_FS_in.FragPos = vertex_info_GS_in[2].FragPos;
	vertex_info_FS_in.Normal   = vertex_info_GS_in[2].Normal;
	vertex_info_FS_in.TexCoord = vertex_info_GS_in[2].TexCoord;
	EmitVertex();

	EndPrimitive();

	//Only generate grass if it's above a world height of 1, so it doesn't generate underwater
	if(vertex_info_GS_in[0].WorldPos.y > 1.0f)
	{
			gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.0f, -0.2f, 0.0f); EmitVertex();
			gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.0f,  0.2f, 0.0f); EmitVertex();
			gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.5f,  0.0f,  0.0f); EmitVertex();
			EndPrimitive();

			gl_Position = u_PV * vertex_info_GS_in[1].WorldPos + u_PVM * vec4(0.2f,  0.0f,  0.0f, 0.0f); EmitVertex();
			gl_Position = u_PV * vertex_info_GS_in[1].WorldPos + u_PVM * vec4(-0.2f,  0.0f, -0.2f, 0.0f); EmitVertex();
			gl_Position = u_PV * vertex_info_GS_in[1].WorldPos + u_PVM * vec4(0.0f,  0.5f,  0.0f,  0.0f); EmitVertex();
			EndPrimitive();

			gl_Position = u_PV * vertex_info_GS_in[2].WorldPos + u_PVM * vec4(0.0f,  0.0f, -0.2f, 0.0f); EmitVertex();
			gl_Position = u_PV * vertex_info_GS_in[2].WorldPos + u_PVM * vec4(0.2f,  0.0f,  0.2f, 0.0f); EmitVertex();
			gl_Position = u_PV * vertex_info_GS_in[2].WorldPos + u_PVM * vec4(0.0f,  0.5f,  0.0f,  0.0f); EmitVertex();
			EndPrimitive();
	}
}