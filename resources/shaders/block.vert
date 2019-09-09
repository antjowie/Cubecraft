#version 450 core
layout (location = 0) in vec3 aPos;

uniform mat4 aMVP;

void main()
{
    gl_Position = aMVP * vec4(aPos, 1);
}