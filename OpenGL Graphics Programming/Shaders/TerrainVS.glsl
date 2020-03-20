#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform float u_time;
uniform mat4 u_PVM;
uniform mat4 u_modelMat;

uniform sampler2D u_grassTex;
uniform sampler2D u_perlinNoiseTex;

out vec3 fragmentPos;
out vec3 fragmentNormal;
out vec2 fragmentTextureCoord;

void main(void)
{
	double yPos = sin(texture2D(u_perlinNoiseTex, vec2(textureCoord.x / 20, textureCoord.y / 20)).r);
	gl_Position = u_PVM * vec4(position.x, yPos, position.z, 1.0f);
	fragmentPos = vec3(u_modelMat * vec4(position, 1.0f));
	fragmentNormal = normal;
	fragmentTextureCoord = textureCoord; 
}