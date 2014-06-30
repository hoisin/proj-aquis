#version 330 core

in vec3 normalVert;
in vec3 colorVert;

out vec3 color;

void main() 
{

	color = colorVert;
}