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
	vec3 lightDir = normalize(vec3(0,0,0) - pos.xyz);
	
	float lamb = max(dot(lightDir, normal), 0.0);
	float spec = 0.0;
	
	if(lamb > 0.0) {
		vec3 viewDir = normalize(-pos.xyz);
		
		vec3 halfDir = normalize(lightDir + viewDir);
		float specAngle = max(dot(halfDir, normal), 0.0);
		spec = pow(specAngle, 16);	
	}
	
	vec3 colour = vec3(0.1,0,0) + lamb * texture( diffuseTextureSampler, UV ).rgb + spec * vec3(1.0, 1.0, 1.0);
	
	// output color as texture
	color = colour;

}