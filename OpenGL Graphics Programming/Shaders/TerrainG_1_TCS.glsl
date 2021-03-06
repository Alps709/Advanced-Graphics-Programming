#version 450 core

//size of output patch & no. of times the TCS will be executed 
layout (vertices = 3) out; 

// attributes of the input 

//Need the world pos for the fog
in VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_TCS_in[];

out VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_TES_in[];

uniform vec3 u_cameraPos;

void main() 
{
	vec4 worldPos = vertex_info_TCS_in[gl_InvocationID].WorldPos;

	// Set the control points of the output patch
	vertex_info_TES_in[gl_InvocationID].WorldPos = worldPos;
	vertex_info_TES_in[gl_InvocationID].FragPos = vertex_info_TCS_in[gl_InvocationID].FragPos;
    vertex_info_TES_in[gl_InvocationID].Normal   = vertex_info_TCS_in[gl_InvocationID].Normal;
    vertex_info_TES_in[gl_InvocationID].TexCoord = vertex_info_TCS_in[gl_InvocationID].TexCoord;

	if (gl_InvocationID == 0) 
	{
		//Calculate camera distance from control point, to determine LOD
		float camDistance = distance(u_cameraPos, worldPos.xyz);

		gl_TessLevelInner[0] = min(20.0 / camDistance, 6);	   	   
		gl_TessLevelOuter[0] = min(20.0 / camDistance, 6);
		gl_TessLevelOuter[1] = min(20.0 / camDistance, 6);
		gl_TessLevelOuter[2] = min(20.0 / camDistance, 6);
	}	

	gl_out[gl_InvocationID].gl_Position = worldPos;
}