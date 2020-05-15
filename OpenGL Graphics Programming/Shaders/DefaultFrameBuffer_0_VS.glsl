#version 450 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 textureCoord;

out vec2 fragmentTextureCoord;

void main(void)
{
	gl_Position = vec4(position.x, position.y, 0.0f, 1.0f);
	fragmentTextureCoord.x = textureCoord.x;
	fragmentTextureCoord.y = -textureCoord.y;
}