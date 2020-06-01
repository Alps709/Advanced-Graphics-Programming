#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform mat4 u_modelMat;

uniform sampler2D u_heightMapTex;
uniform float u_heightModifier = 1.0f;

out VERTEX_INFO
{
	vec3 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_TCS_in;

void main(void)
{
	//Displace the vertex along the normal
	float Displacement = texture(u_heightMapTex, textureCoord.xy).r;
	vec3 tempPos = position;

	tempPos.y += Displacement * u_heightModifier;

	gl_Position = u_modelMat * vec4(tempPos, 1.0f);
	
	vertex_info_TCS_in.WorldPos = vec3(u_modelMat * vec4(tempPos, 1.0f));
	vertex_info_TCS_in.FragPos= vec3(u_modelMat * vec4(tempPos, 1.0f));
	vertex_info_TCS_in.Normal = normal;
	vertex_info_TCS_in.TexCoord = textureCoord; 
}