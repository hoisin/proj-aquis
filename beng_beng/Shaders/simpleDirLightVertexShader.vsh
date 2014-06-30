#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;
uniform mat4 worldInMatrix;		// Inverse transpose world matrix

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexColor;

out vec3 normalVert;
out vec3 colorVert;

// main routine
void main()
{
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(vertexPosition_modelspace, 1.0);
	normalVert = worldInvMatrix * vec4(vertexNormal, 1.0);
	
	colorVert = vertexColor;
}