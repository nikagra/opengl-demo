#version 430 core

layout (location = 0) in vec3 inPosition;
layout (location = 1) in vec3 vColor;

out vec4 fColor;

uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform mat4 projectionMatrix;

void main()
{
    gl_Position = (projectionMatrix * viewMatrix * modelMatrix) * vec4(inPosition, 1.0);
	fColor = vec4(vColor, 1.0);
}
