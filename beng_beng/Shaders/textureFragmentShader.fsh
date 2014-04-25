#version 330 core

in vec2 UV;

out vec3 color;

uniform sampler2D myTextureSampler;

void main() 
{
	// output color as texture
	color = texture( myTextureSampler, UV ).rgb;

}