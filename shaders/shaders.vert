#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec4 aColor;

uniform mat4 transform;
out vec4 ourColor; 

void main()
{
    gl_Position = transform * vec4(aPos, 1.0);
    ourColor = aColor;
}

