#version 450 core

//Vertex inputs
in vec3 fragmentPos;
in vec3 fragmentNormal;
in vec2 fragmentTextureCoord;
in vec4 mWorldPos;

//Colour output
out vec4 colour;

//Texture
uniform sampler2D u_grassTex;
uniform vec3 u_camPos;
uniform bool u_fogRenderMode;

vec4 vFogColor = vec4(0.5f, 0.5f, 0.5f, 1.0f);

//Ambient lighting
uniform float u_ambientStr    = 0.25f;
uniform vec3  u_ambientColour = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  u_lightColour   = vec3(1.0f, 1.0f, 1.0f);
uniform vec3  u_lightPos      = vec3(0.0f, 100.0f, 1000.0f);

//Blinn - Phong lighting
uniform float u_lightSpecStr  = 1.0f;
uniform float u_shininess     = 32.0f;

void main(void)
{
	//Ambient light
	vec3 ambient = u_ambientStr * u_ambientColour;

	//Light Direction
	vec3 norm = normalize(fragmentNormal);
	vec3 lightDir = normalize(u_lightPos - fragmentPos);

	//Diffuse colouring
	float diffuseStr = max(dot(norm, lightDir), 0.0f);
	vec3 diffuse = diffuseStr * u_lightColour;

	//Specular highlight
	vec3 negViewDir = normalize(u_camPos - fragmentPos);

	//Phong lighting uses the light reflection direction
	//vec3 reflectDir = reflect(-lightDir, norm);

	//Use Blinn - Phong lighting by using halfway vec, instead of reflection direction
	vec3 halfwayVec = normalize(-lightDir + negViewDir);
	float spec = pow(max(dot(norm, halfwayVec), 0.0f), u_shininess);
	vec3 specular = u_lightSpecStr * spec * u_lightColour;

	//Fog
	float d = distance(mWorldPos.xyz, u_camPos);
	float lerp = (d - 5.0f)/50.f;
	lerp = clamp(lerp, 0.0, 1.0);

	vec4 texColour = texture(u_grassTex, fragmentTextureCoord);

	vec4 finalColour = vec4(ambient + diffuse + specular, 1.0f) * texColour;

	if(u_fogRenderMode)
	{
		colour = mix(finalColour, vFogColor, lerp);
	}
	else
	{
	    colour = finalColour;
	}
}