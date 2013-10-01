#version 430 core

layout (location = 0) in vec2 inPosition;
layout (location = 1) in vec3 vColor;

out vec4 fColor;

void main()
{
    gl_Position = vec4(inPosition, 0.0, 1.0);
	fColor = vec4(vColor, 1.0);
}
