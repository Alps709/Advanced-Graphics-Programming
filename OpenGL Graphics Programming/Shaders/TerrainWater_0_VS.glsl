#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform float u_time;
uniform mat4 u_PVM;
uniform mat4 u_modelMat;

//Perlin noise texture used to make the waves wavvy
uniform sampler2D u_perlinNoiseTex;

//Need the world pos for the fog
out vec4 mWorldPos;

out vec3 fragmentNormal;
out vec2 fragmentTextureCoord;

void main(void)
{
	float smallTime = u_time * 0.01;
	double yPos = (sin(texture2D(u_perlinNoiseTex, vec2(textureCoord.x/20, textureCoord.y/20)).r * smallTime)/2 + 1) * 0.15f;
	
	gl_Position = u_PVM * vec4(position.x, yPos - 0.15f, position.z, 1.0f);

	mWorldPos = u_modelMat * vec4(position, 1.0f);

	fragmentNormal = normal;
	fragmentTextureCoord = textureCoord; 
}