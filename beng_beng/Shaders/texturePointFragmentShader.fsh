#version 330 core

#define MAX_LIGHTS 4

in vec4 pos;
in vec3 norm;
in vec2 UV;

out vec3 color;

uniform sampler2D diffuseTextureSampler;

void main() 
{
	vec3 normal = normalize(norm);
	vec3 lightDir = normalize(vec3(0,100,0) - pos.xyz);
	
	float lamb = max(dot(lightDir, normal), 0.0);
	
	vec3 colour = vec3(0.1,0,0) + lamb * texture( diffuseTextureSampler, UV ).rgb;
	
	// output color as texture
	color = colour;

}