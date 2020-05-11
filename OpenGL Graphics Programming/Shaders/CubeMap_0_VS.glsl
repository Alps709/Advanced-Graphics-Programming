#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec2 textureCoord;

uniform mat4 u_PVM;
uniform mat4 u_modelMat;
uniform vec3 u_camPos;

//Need the world pos for the fog
out vec4 mWorldPos;

out vec3 fragmentTextureCoord;

void main()
{
	gl_Position = u_PVM * vec4(position, 1.0f);

	mWorldPos = u_modelMat * vec4(position, 1.0f);

	fragmentTextureCoord = position;
}