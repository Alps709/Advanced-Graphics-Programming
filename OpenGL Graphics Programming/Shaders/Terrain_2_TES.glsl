#version 450 core

layout (triangles, equal_spacing, ccw) in;

uniform sampler2D u_heightMapTex;
float heightModifier = 30.0f;

uniform mat4 u_PV;

in VERTEX_INFO
{
	vec3 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_TES_in[];

out VERTEX_INFO
{
	vec3 WorldPos;
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoord;
} vertex_info_FS_in;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)
{
    return vec2(gl_TessCoord.x) * v0 + vec2(gl_TessCoord.y) * v1 + vec2(gl_TessCoord.z) * v2;
}

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)
{
    return vec3(gl_TessCoord.x) * v0 + vec3(gl_TessCoord.y) * v1 + vec3(gl_TessCoord.z) * v2;
}

void main(void)
{
	//Interpolate the attributes of the output vertex using the barycentric coordinates
    vertex_info_FS_in.TexCoord = interpolate2D(vertex_info_TES_in[0].TexCoord, vertex_info_TES_in[1].TexCoord, vertex_info_TES_in[2].TexCoord);

	vertex_info_FS_in.WorldPos = interpolate3D(vertex_info_TES_in[0].WorldPos, vertex_info_TES_in[1].WorldPos, vertex_info_TES_in[2].WorldPos);

	//HOW TO DO IT IF YOU'RE USING A DISPLACEMENT HEIGHTMAP TEXTURE
    float Displacement = texture(u_heightMapTex, vertex_info_FS_in.TexCoord.xy).r;
    vertex_info_FS_in.WorldPos.y = Displacement * heightModifier;

	vertex_info_FS_in.FragPos = vertex_info_FS_in.WorldPos;

    gl_Position = u_PV * vec4(vertex_info_FS_in.WorldPos, 1.0);
	
	vertex_info_FS_in.WorldPos = gl_Position.xyz;
}

