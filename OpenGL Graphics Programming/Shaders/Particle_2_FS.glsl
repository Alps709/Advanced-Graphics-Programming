#version 450 core

in GS_FS_VERTEX
{
	vec2 texcoord;
}fs_in;

uniform sampler2D u_tex;

out vec4 colour;

void main()
{
	colour = texture2D(u_tex, vec2(fs_in.texcoord.x, fs_in.texcoord.y));
}