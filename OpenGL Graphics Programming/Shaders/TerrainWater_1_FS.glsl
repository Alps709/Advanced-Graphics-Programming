#version 450 core

//Vertex inputs
in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;
in vec4 mWorldPos;

//Colour output
out vec4 colour;

//Texture
uniform sampler2D u_terrainTex;
uniform vec3 u_camPos;
uniform bool u_fogRenderMode;

vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

void main(void)
{
	float d = distance(mWorldPos.xyz, u_camPos);
	float lerp = (d - 5.0f)/50.f;
	lerp = clamp(lerp, 0.0, 1.0);
	
	//Make the texture blue and slightly transparent
	vec4 texColour = texture(u_terrainTex, fragmentTextureCoord) * vec4(0.0f, 0.1f, 1.0f, 0.75f);

	if(u_fogRenderMode)
	{
		colour = mix(texColour, vFogColor, lerp);
	}
	else
	{
	    colour = texColour;
	}
}