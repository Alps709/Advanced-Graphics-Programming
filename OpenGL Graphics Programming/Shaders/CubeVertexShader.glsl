#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform mat4 u_PVM;
uniform mat4 u_projMat;
uniform mat4 u_viewMat;
uniform mat4 u_modelMat;

uniform sampler2D u_grassTex;

out vec3 fragmentPos;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoord;

void main(void)
{
	gl_Position = u_PVM * vec4(position.x, position.y * 1.25f, position.z, 1.0f);
	//fragmentPos = vec3(u_modelMat * vec4(position, 1.0f));
	fragmentNormal = normal;
	fragmentTextureCoord = textureCoord; 
}