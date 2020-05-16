#version 450 core

//Vertex inputs

in VERTEX_INFO
{
	vec3 WorldPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_FS_in;

//Colour output
out vec4 colour;

//Uniforms

//Texture
uniform sampler2D u_grassTex;

uniform vec3 u_camPos;
uniform bool u_fogRenderMode;

vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

void main(void)
{
	//Fog
	float d = distance(vertex_info_FS_in.WorldPos.xyz, u_camPos);
	float lerp = (d - 5.0f)/50.f;
	lerp = clamp(lerp, 0.0, 1.0);
	vec4 texColour = texture(u_grassTex, vertex_info_FS_in.TexCoord);

	if(u_fogRenderMode)
	{
		colour = mix(texColour, vFogColor, lerp);
	}
	else
	{
	    colour = texColour;
	}
}