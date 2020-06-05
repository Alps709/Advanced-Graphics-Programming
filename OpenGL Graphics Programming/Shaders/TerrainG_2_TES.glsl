#version 450 core

layout (triangles, equal_spacing, ccw) in;

uniform sampler2D u_heightMapTex;
uniform float u_heightModifier = 30.0f;

in VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_TES_in[];

out VERTEX_INFO
{
	vec4 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_GS_in;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec4 interpolate3D(vec4 v0, vec4 v1, vec4 v2)
{
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

void main(void)
{
	//Interpolate the attributes of the output vertex using the barycentric coordinates
	vertex_info_GS_in.TexCoord = interpolate2D(vertex_info_TES_in[0].TexCoord, vertex_info_TES_in[1].TexCoord, vertex_info_TES_in[2].TexCoord);

	vertex_info_GS_in.WorldPos = interpolate3D(vertex_info_TES_in[0].WorldPos, vertex_info_TES_in[1].WorldPos, vertex_info_TES_in[2].WorldPos);

	vec4 fragPos0 = vec4(vertex_info_TES_in[0].FragPos, 1.0f);
	vec4 fragPos1 = vec4(vertex_info_TES_in[1].FragPos, 1.0f);
	vec4 fragPos2 = vec4(vertex_info_TES_in[2].FragPos, 1.0f);

	vertex_info_GS_in.FragPos = interpolate3D(fragPos0, fragPos1, fragPos2).xyz;

	//HOW TO DO IT IF YOU'RE USING A DISPLACEMENT HEIGHTMAP TEXTURE
    float Displacement = texture(u_heightMapTex, vertex_info_GS_in.TexCoord.xy).r;
	vertex_info_GS_in.WorldPos.y = Displacement * u_heightModifier;

    gl_Position = vertex_info_GS_in.WorldPos;
	
	vertex_info_GS_in.WorldPos = gl_Position;
}

