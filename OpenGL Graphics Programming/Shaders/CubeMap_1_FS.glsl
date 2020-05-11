#version 450 core

in vec3 fragmentTextureCoord;
in vec4 mWorldPos;

out vec4 colour;

uniform samplerCube u_cubeSampler;

uniform vec3 u_camPos;
uniform bool u_fogRenderMode;

vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

void main()
{
	float d = distance(mWorldPos.xyz, u_camPos);
	float lerp = (d - 5.0f)/50.f;
	lerp = clamp(lerp, 0.0, 1.0);

	vec4 texColour = texture(u_cubeSampler, fragmentTextureCoord);

	if(u_fogRenderMode)
	{
		colour = mix(texColour, vFogColor, lerp);
	}
	else
	{
	    colour = texColour;
	}
}