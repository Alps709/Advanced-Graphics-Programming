#version 450 core

in vec2 fragmentTextureCoord;

out vec4 colour;

uniform sampler2D u_renderTex;

uniform float u_currentTime;

uniform vec3 u_resolution = vec3(1280.0f, 720.0f, 0.0f);

void main()
{
	//Distance from the center of the image
	//Used for blur
	vec2 uv = fragmentTextureCoord;
	float centerDistance = length(uv - vec2(0.5f, 0.5f));
	
	// blur amount
	float blur = (1.0f + sin(u_currentTime * 6.0f)) * 0.5f;
	blur *= 1.0f + sin(u_currentTime * 16.0f) * 0.5f;
	blur = pow(blur, 3.0f);
	blur *= 0.05f;
	//Remove blur closer to the center
	blur *= centerDistance;
	
	// final color
    vec3 finalColour;
    finalColour.r = texture2D(u_renderTex, vec2(uv.x + blur, uv.y)).r;
    finalColour.g = texture2D(u_renderTex, uv).g;
    finalColour.b = texture2D(u_renderTex, vec2(uv.x - blur, uv.y)).b;
	
	// scanline
	float scanline = sin(uv.y * u_resolution.y) * 0.04f;
	finalColour -= scanline;
	
	// vignette
	finalColour *= 1.0f - centerDistance * 0.5f;

	colour = vec4(finalColour, 1.0f);
}