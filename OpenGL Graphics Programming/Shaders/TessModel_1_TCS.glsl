#version 450 core

uniform float u_cameraDistance;

//size of output patch & no. of times the TCS will be executed 
layout (vertices = 4) out; 

void main() 
{
	if (gl_InvocationID == 0) 
	{
		gl_TessLevelInner[0] = 4.0 / u_cameraDistance;
		gl_TessLevelInner[1] = 4.0 / u_cameraDistance;

		gl_TessLevelOuter[0] = 6.0 / u_cameraDistance;
		gl_TessLevelOuter[1] = 6.0 / u_cameraDistance;
		gl_TessLevelOuter[2] = 6.0 / u_cameraDistance;
		gl_TessLevelOuter[3] = 6.0 / u_cameraDistance;

	}	

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}