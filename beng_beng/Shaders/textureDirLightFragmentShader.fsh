#version 330 core

in vec3 normalVert;
in vec2 UV;

out vec4 outputColor;

uniform sampler2D myTextureSampler;

uniform vec3 lightDirection;
uniform vec4 diffuseLightCol;
uniform vec3 ambLightCol;
uniform float ambIntensity;

void main() 
{
	vec3 lightDir;
	float lightIntensity;
	
	// invert the light direction for calculations
	lightDir = -lightDirection;
	
	// Calculate the amount of light on this pixel
	lightIntensity = clamp(dot(normalVert, lightDir), 0.0f, 1.0f);
	
	// Determine the final amount of diffuse color based on the diffuse color combined with the light intensity
	outputColor = clamp((diffuseLightCol * lightIntensity), 0.0f, 1.0f);
	
	// Multiple the light colour with the object's diffuse colour to get final result
	outputColor = vec4(texture( myTextureSampler, UV ).rgb, 1) * outputColor + vec4((ambLightCol * ambIntensity), 1);
}