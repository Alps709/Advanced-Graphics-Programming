#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec4 colour;
layout (location = 2) in vec2 textureCoord;

uniform mat4 u_PVM;
uniform mat4 u_modelMat;

uniform sampler2D u_grassTex;

//Need the world pos for the fog
out vec4 mWorldPos;

out vec4 fragmentColour;
out vec2 fragmentTextureCoord;

void main(void)
{
	gl_Position = u_PVM * vec4(position.x, position.y, position.z, 1.0f);

	mWorldPos = u_modelMat * vec4(position, 1.0f);

	fragmentColour = colour;
	fragmentTextureCoord = textureCoord; 
}