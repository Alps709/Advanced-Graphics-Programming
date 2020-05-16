#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform mat4 u_modelMat;

out VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_TCS_in;

void main(void)
{
	gl_Position = u_modelMat * vec4(position, 1.0f);
	
	vertex_info_TCS_in.WorldPos = u_modelMat * vec4(position, 1.0f);
	vertex_info_TCS_in.FragPos = vec3(u_modelMat * vec4(position, 1.0f));
	vertex_info_TCS_in.Normal = normal;
	vertex_info_TCS_in.TexCoord = textureCoord; 
}