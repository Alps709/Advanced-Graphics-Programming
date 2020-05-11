#version 450 core

in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;

out vec4 colour;

uniform sampler2D u_tex;

uniform float u_ambientStr    = 0.25f;
uniform vec3  u_ambientColour = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  u_lightColour   = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  u_lightPos      = vec3(0.0f, 600.0f, 0.0f);

uniform vec3  u_camPos;
uniform float u_lightSpecStr  = 1.0f;
uniform float u_shininess     = 32.0f;

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

	//Phong lighting uses reflection direction
	//vec3 reflectDir = reflect(lightDir, norm);

	//Use blin - phong by using halfway vec, instead of reflection direction
	vec3 halfwayVec = normalize(-lightDir + negViewDir);
	float spec = pow(max(dot(norm, halfwayVec), 0.0f), u_shininess);
	vec3 specular = u_lightSpecStr * spec * u_lightColour;

	colour = vec4(ambient + diffuse + specular, 1.0f) * (texture(u_tex, fragmentTextureCoord));
}