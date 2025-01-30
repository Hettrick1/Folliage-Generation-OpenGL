#version 330 core

layout (location = 0) in vec3 a_Position;
layout (location = 1) in vec3 a_InstancePosition;
layout (location = 2) in float a_Rotation;

uniform mat4 u_MVP;

void main()
{
    float c = cos(a_Rotation);
    float s = sin(a_Rotation);
    mat4 rotationMatrix = mat4(
        c, -s, 0.0, 0.0,
        s,  c, 0.0, 0.0,
        0.0, 0.0, 1.0, 0.0,
        0.0, 0.0, 0.0, 1.0
    );

    vec4 rotatedPosition = rotationMatrix * vec4(a_Position, 1.0);
    vec4 worldPosition = vec4(a_InstancePosition, 1.0) + rotatedPosition;

    gl_Position = u_MVP * worldPosition;
}