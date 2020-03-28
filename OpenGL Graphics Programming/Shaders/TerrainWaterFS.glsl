#version 450 core

//Vertex inputs
in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;

//Colour output
out vec4 colour;

//Texture
uniform sampler2D u_grassTex;

//Ambient lighting
//uniform float u_ambientStr    = 0.25f;
//uniform vec3  u_ambientColour = vec3(1.0f, 1.0f, 1.0f);
//uniform vec3  u_lightColour   = vec3(1.0f, 1.0f, 1.0f);
//uniform vec3  u_lightPos      = vec3(0.0f, 0.0f, 2000.0f);

void main(void)
{
	//Ambient light
	//vec3 ambient = u_ambientStr * u_ambientColour;

	//Light Direction
	//vec3 norm = normalize(fragmentNormal);
	//vec3 lightDir = normalize(fragmentPos - u_lightPos);

	//Diffuse colouring
	//float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	//vec3 diffuse = diffuseStr * u_lightColour;

	colour = (texture(u_grassTex, fragmentTextureCoord) * vec4(0.0f, 0.1f, 1.0f, 0.75f));
}