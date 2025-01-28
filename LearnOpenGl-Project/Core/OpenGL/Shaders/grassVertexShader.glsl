#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_InstancePos; 

uniform mat4 u_MVP;

void main()
{
    vec3 worldPosition = a_Position + a_InstancePos;
    gl_Position = u_MVP * vec4(worldPosition, 1.0);
}