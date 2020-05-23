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

	//Determine which texture to draw
	vec4 texColour = (useGrassTexture == 0) ? texture(u_terrainTex, vertex_info_FS_in.TexCoord) : texture(u_grassTex, vertex_info_FS_in.TexCoord);

	//Discard the pixel if the transparency is less than 0.99
	if(texColour.a < 0.99f)
	{
		discard;
	}

	//If the world position of this fragment is less than 0
	//then it is below the water level and should be coloured blue
	if(vertex_info_FS_in.FragPos.y < 0.0f)
	{
		texColour.r = 0.0f;
		texColour.g = 0.0f;
	}

	//Final colour can be affected by fog
	if(u_fogRenderMode)
	{
		colour = mix(texColour, vFogColor, lerp);
	}
	else
	{
	    colour = texColour;
	}
}