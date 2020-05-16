#version 450 core

layout (triangles, equal_spacing, ccw) in;

//uniform sampler2D gDisplacementMap;
//uniform float gDispFactor;
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

	//HOW TO DO IT IF YOU'RE USING A DISPLACEMENT HEIGHTMAP TEXTURE
	vertex_info_FS_in.WorldPos = interpolate3D(vertex_info_TES_in[0].WorldPos, vertex_info_TES_in[1].WorldPos, vertex_info_TES_in[2].WorldPos);
	vertex_info_FS_in.FragPos = interpolate3D(vertex_info_TES_in[0].FragPos, vertex_info_TES_in[1].FragPos, vertex_info_TES_in[2].FragPos);
	//Displace the vertex along the normal
    //float Displacement = texture(gDisplacementMap, vertex_info_FS_in.TexCoord.xy).x;
    //vertex_info_FS_in.WorldPos += vertex_info_FS_in.Normal * Displacement * gDispFactor;
    gl_Position = u_PV * vec4(vertex_info_FS_in.WorldPos, 1.0);

//	gl_Position = (gl_TessCoord.x * gl_in[0].gl_Position +
//	               gl_TessCoord.y * gl_in[1].gl_Position +
//	               gl_TessCoord.z * gl_in[2].gl_Position );
	
	vertex_info_FS_in.WorldPos = gl_Position.xyz;
}

