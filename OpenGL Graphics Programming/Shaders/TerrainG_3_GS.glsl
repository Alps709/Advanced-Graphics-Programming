#version 450 core

layout (triangles) in;
layout (triangle_strip, max_vertices = 16) out;

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

out flat int useGrassTexture;

uniform mat4 u_PVM;
uniform mat4 u_PV;

void main() 
{
	//Main terrain triangle pass through
	gl_Position = u_PV * vertex_info_GS_in[0].WorldPos; 
	vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
	vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
	vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
	vertex_info_FS_in.TexCoord = vertex_info_GS_in[0].TexCoord;
	useGrassTexture = 0;
	EmitVertex();

	gl_Position = u_PV * vertex_info_GS_in[1].WorldPos; 
	vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[1].WorldPos;
	vertex_info_FS_in.FragPos = vertex_info_GS_in[1].FragPos;
	vertex_info_FS_in.Normal   = vertex_info_GS_in[1].Normal;
	vertex_info_FS_in.TexCoord = vertex_info_GS_in[1].TexCoord;
	useGrassTexture = 0;
	EmitVertex();

	gl_Position = u_PV * vertex_info_GS_in[2].WorldPos; 
	vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[2].WorldPos;
	vertex_info_FS_in.FragPos = vertex_info_GS_in[2].FragPos;
	vertex_info_FS_in.Normal   = vertex_info_GS_in[2].Normal;
	vertex_info_FS_in.TexCoord = vertex_info_GS_in[2].TexCoord;
	useGrassTexture = 0;
	EmitVertex();

	EndPrimitive();

	//Only generate grass if it's above a world height of 1, so it doesn't generate underwater
	if(vertex_info_GS_in[0].WorldPos.y > 1.0f)
	{

		///First grass quad

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.0f, -0.2f, 0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(0.0f, 1.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.5f,  -0.2f,  0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(0.0f, 0.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.0f,  0.2f, 0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(1.0f, 1.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.5f,  0.2f,  0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(1.0f, 0.0f);
		useGrassTexture = 1;
		EmitVertex();

		EndPrimitive();


		///Second grass quad
		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.0f, -0.2f, 0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(0.0f, 1.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.0f,  0.5f,  -0.2f,  0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(0.0f, 0.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.2f,  0.0f,  0.2f, 0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(1.0f, 1.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.2f,  0.5f,  0.2f,  0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(1.0f, 0.0f);
		useGrassTexture = 1;
		EmitVertex();

		EndPrimitive();



		///Third grass quad
		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.2f,  0.0f, -0.2f, 0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(0.0f, 1.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.2f,  0.5f,  -0.2f,  0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(0.0f, 0.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.2f,  0.0f,  0.2f, 0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(1.0f, 1.0f);
		useGrassTexture = 1;
		EmitVertex();

		gl_Position = u_PV * vertex_info_GS_in[0].WorldPos + u_PVM * vec4(0.2f,  0.5f,  0.2f,  0.0f); 
		vertex_info_FS_in.WorldPos = u_PV * vertex_info_GS_in[0].WorldPos;
		vertex_info_FS_in.FragPos = vertex_info_GS_in[0].FragPos;
		vertex_info_FS_in.Normal   = vertex_info_GS_in[0].Normal;
		vertex_info_FS_in.TexCoord = vec2(1.0f, 0.0f);
		useGrassTexture = 1;
		EmitVertex();

		EndPrimitive();

	}
}