#version 450 core

uniform float u_cameraDistance;

//size of output patch & no. of times the TCS will be executed 
layout (vertices = 4) out; 

void main() 
{
	if (gl_InvocationID == 0) 
	{
		gl_TessLevelInner[0] = min(20.0 / u_cameraDistance, 5);
		gl_TessLevelInner[1] = min(20.0 / u_cameraDistance, 5);
							   	   
		gl_TessLevelOuter[0] = min(20.0 / u_cameraDistance, 5);
		gl_TessLevelOuter[1] = min(20.0 / u_cameraDistance, 5);
		gl_TessLevelOuter[2] = min(20.0 / u_cameraDistance, 5);
		gl_TessLevelOuter[3] = min(20.0 / u_cameraDistance, 5);
	}	

	gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}