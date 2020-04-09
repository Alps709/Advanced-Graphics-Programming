#version 450 core

//Vertex inputs
in vec3 fragmentPos;
in vec4 fragmentColour;
in vec2 fragmentTextureCoord;
in vec4 mWorldPos;

//Colour output
out vec4 colour;

//Texture
uniform sampler2D u_grassTex;

uniform vec3 u_camPos;
uniform bool u_fogRenderMode;
uniform bool u_stencilOutline;

vec4 stencilOutlineColour = vec4(1.0f, 0.0f, 0.0f, 1.0f);

vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

void main(void)
{
	float d = distance(mWorldPos.xyz, u_camPos);
	float lerp = (d - 5.0f)/100.f;
	lerp = clamp(lerp, 0.0, 1.0);

	vec4 finalColour;

	if(u_stencilOutline)
	{
		finalColour = stencilOutlineColour;
	}
	else
	{
		finalColour = texture(u_grassTex, fragmentTextureCoord);
	}

	if(u_fogRenderMode)
	{
		colour = mix(finalColour, vFogColor, lerp);
	}
	else
	{
	    colour = finalColour;
	}
}