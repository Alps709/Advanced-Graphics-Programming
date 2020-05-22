#version 450 core

//Vertex inputs
in VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_FS_in;

in flat int useGrassTexture;

//Colour output
out vec4 colour;

//Uniforms

//Textures
uniform sampler2D u_terrainTex;
uniform sampler2D u_grassTex;

uniform vec3 u_camPos;
uniform bool u_fogRenderMode;
uniform bool u_underWater;

vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

void main(void)
{
	//Fog
	float d = distance(vertex_info_FS_in.WorldPos.xyz, u_camPos);
	float lerp = (d - 5.0f)/50.0f;
	lerp = clamp(lerp, 0.0f, 1.0f);
	vec4 texColour = (useGrassTexture == 0) ? texture(u_terrainTex, vertex_info_FS_in.TexCoord) : texture(u_grassTex, vertex_info_FS_in.TexCoord);

	if(texColour.a < 0.5f)
	{
		discard;
	}

	if(vertex_info_FS_in.FragPos.y < 0.0f)
	{
		texColour.r = 0.0f;
		texColour.g = 0.0f;
	}

	if(u_fogRenderMode)
	{
		colour = mix(texColour, vFogColor, lerp);
	}
	else
	{
	    colour = texColour;
	}
}