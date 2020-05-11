#version 450 core

//Vertex inputs
in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;

//Colour output
out vec4 colour;

//Texture
uniform sampler2D u_tex;

//Camera position for lighting
uniform vec3  u_camPos;

//Ambient lighting
uniform float u_ambientStr    = 0.25f;
uniform vec3  u_ambientColour = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  u_lightColour   = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  u_lightPos      = vec3(0.0f, 600.0f, 0.0f);

//Blinn - Phong lighting
uniform float u_lightSpecStr  = 1.0f;
uniform float u_shininess     = 32.0f;

//Rim lighting
uniform int u_rimExponent = 2;
uniform vec3 u_rimColour = vec3(1.0f, 0.0f, 0.0f);


void main(void)
{
	//Ambient light
	vec3 ambient = u_ambientStr * u_ambientColour;

	//Light Direction
	vec3 norm = normalize(fragmentNormal);
	vec3 lightDir = normalize(fragmentPos - u_lightPos);

	//Diffuse colouring
	float diffuseStr = max(dot(norm, -lightDir), 0.0f);
	vec3 diffuse = diffuseStr * u_lightColour;

	//Specular highlight
	vec3 negViewDir = normalize(u_camPos - fragmentPos);

	//Phong lighting uses the light reflection direction
	//vec3 reflectDir = reflect(lightDir, norm);

	//Use Blinn - Phong lighting by using halfway vec, instead of reflection direction
	vec3 halfwayVec = normalize(-lightDir + negViewDir);
	float spec = pow(max(dot(norm, halfwayVec), 0.0f), u_shininess);
	vec3 specular = u_lightSpecStr * spec * u_lightColour;

	//Rim lighting
	float rimFactor = 1.0f - dot(norm, negViewDir);
	rimFactor = smoothstep(0.0, 1.0, rimFactor);
	rimFactor = pow(rimFactor, u_rimExponent);
	vec3 rim = rimFactor * u_rimColour * u_lightColour;

	colour = vec4(ambient + diffuse + specular + rim, 1.0f) * (texture(u_tex, fragmentTextureCoord));
}