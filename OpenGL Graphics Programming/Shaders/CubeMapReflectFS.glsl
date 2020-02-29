#version 450 core

in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;

out vec4 colour;

uniform vec3 u_camPos;
uniform samplerCube u_skyBox;

void main()
{
	vec3 norm = normalize(fragmentNormal);
	vec3 viewDir = normalize(fragmentPos - u_camPos);
	vec3 reflectDir = reflect(viewDir, norm);

	colour = vec4(texture(u_skyBox, reflectDir).rgb, 1.0f);
}