#version 330 core

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 worldMatrix;
uniform mat4 worldInvMatrix;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec2 vertexUV;

out vec3 normalVert;
out vec2 UV;

// main routine
void main()
{
	gl_Position = projectionMatrix * viewMatrix * worldMatrix * vec4(vertexPosition_modelspace, 1.0);	
	UV = vertexUV;
	
	// Calculate the normal vector against world matrix only
	normalVert = mat3(worldInvMatrix) * vertexNormal;
	
	// Normalize the normal vector
	normalVert = normalize(normalVert);
}